#include <stdio.h>
#include <stdlib.h>

extern char **environ;

static void print_env(const char *s) {
    for (; *s; s++) {
        switch (*s) {
            case '&': fputs("&amp;", stdout); break;
            case '<': fputs("&lt;", stdout); break;
            case '>': fputs("&gt;", stdout); break;
            case '"': fputs("&quot;", stdout); break;
            default:  fputc(*s, stdout);
        }
    }
}

int main(void) {
    printf("Content-Type: text/html\r\n\r\n");

    printf("<!doctype html><html lang=\"en\"><head>"
           "<meta charset=\"utf-8\">"
           "<title>C Environment Variables</title>"
           "<style>"
           "header{text-align:center;}"
           "</style></head><body>"
           "<header><h1>C Environment Variables</h1><hr></header>"
           "<main><ul>");

    for (char **p = environ; *p; p++) {
        const char *kv = *p;
        const char *eq = kv;
        while (*eq && *eq != '=') eq++;

        fputs("<li><b>", stdout);
        for (const char *k = kv; k < eq; k++) print_env((char[]){*k,0});
        fputs("</b> = ", stdout);

        if (*eq == '=') print_env(eq + 1);
        fputs("</li>", stdout);
    }

    printf("</ul></main></body></html>");
    return 0;
}
