#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define COOKIE "CSE135_SESSION_ID"

static char *get_cookie(const char *hdr)
{
    if (!hdr)
        return NULL;
    const char *p = strstr(hdr, COOKIE "=");
    if (!p)
        return NULL;
    p += strlen(COOKIE) + 1;
    const char *end = strchr(p, ';');
    size_t len = end ? (size_t)(end - p) : strlen(p);
    char *v = malloc(len + 1);
    memcpy(v, p, len);
    v[len] = 0;
    return v;
}

static char *read_body(void)
{
    const char *cl = getenv("CONTENT_LENGTH");
    long n = cl ? strtol(cl, NULL, 10) : 0;
    if (n <= 0)
        return strdup("");
    char *buf = malloc((size_t)n + 1);
    fread(buf, 1, (size_t)n, stdin);
    buf[n] = 0;
    return buf;
}

static void url_decode(char *s)
{
    char *o = s;
    while (*s)
    {
        if (*s == '+')
        {
            *o++ = ' ';
            s++;
        }
        else if (*s == '%' && s[1] && s[2])
        {
            char v = (char)((strtol((char[]){s[1], s[2], 0}, NULL, 16)));
            *o++ = v;
            s += 3;
        }
        else
            *o++ = *s++;
    }
    *o = 0;
}

int main(void)
{
    const char *qs = getenv("QUERY_STRING");
    const char *method = getenv("REQUEST_METHOD");
    const char *cookie_hdr = getenv("HTTP_COOKIE");

    char *sid = get_cookie(cookie_hdr);
    if (!sid)
    {
        char tmp[64];
        snprintf(tmp, sizeof(tmp), "%ld", (long)getpid());
        sid = strdup(tmp);
    }

    char path[256];
    snprintf(path, sizeof(path), "/tmp/cse135_state_%s", sid);

    // --- clear ---
    if (qs && strstr(qs, "clear=1"))
    {
        unlink(path);
        printf("Status: 302 Found\r\n");
        printf("Set-Cookie: %s=%s; Path=/\r\n", COOKIE, sid);
        printf("Location: state-c\r\n\r\n");
        free(sid);
        return 0;
    }

    // --- save ---
    if (method && strcmp(method, "POST") == 0)
    {
        char *body = read_body();
        char *p = strstr(body, "name=");
        if (p)
        {
            p += 5;
            url_decode(p);
            FILE *f = fopen(path, "w");
            if (f)
            {
                fputs(p, f);
                fclose(f);
            }
        }
        free(body);
    }

    // --- load ---
    char name[256] = "(nothing set yet)";
    FILE *f = fopen(path, "r");
    if (f)
    {
        fgets(name, sizeof(name), f);
        fclose(f);
    }

    // --- output ---
    printf("Content-Type: text/html\r\n");
    printf("Set-Cookie: %s=%s; Path=/\r\n\r\n", COOKIE, sid);
    printf("<p><b>HTTP Protocol:</b> %s</p>", getenv("SERVER_PROTOCOL"));
    printf("<p><b>HTTP Method:</b> %s</p>", getenv("REQUEST_METHOD"));
    printf("<p><b>Query String:</b> %s</p>", getenv("QUERY_STRING"));

    printf("<!doctype html><html><head><meta charset=\"utf-8\"><title>State (C)</title></head><body>");
    printf("<h1>State Page (C)</h1>");
    printf("<p><b>Saved name:</b> %s</p>", name);
    printf("<p>"
           "<a href=\"/session/c-cgiform.html\">Back to form</a> | "
           "<a href=\"/index.html\">Home</a> | "
           "<a href=\"state-c?clear=1\">Clear</a>"
           "</p>");
    printf("</body></html>");

    free(sid);
    return 0;
}
