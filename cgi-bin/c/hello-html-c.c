#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    const char *ip = getenv("REMOTE_ADDR");
    if (!ip) ip = "unknown";

    time_t t = time(NULL);
    struct tm *currentTime = localtime(&t);

    printf("Content-Type: text/html\r\n\r\n");

    printf("<!doctype html><html lang=\"en\"><head>"
           "<meta charset=\"utf-8\">"
           "<title>Hello, C!</title>"
           "<style>"
           "header{text-align:center;}"
           "</style>"
           "</head><body>"
           "<header><h1>Hello, C!</h1><hr></header>"
           "<main>"
           "<p>Hello World from Team Kook!</p>"
           "<p>This page was generated with the C programming language.</p>"
           "<p>Today's date is %04d-%02d-%02d %02d:%02d:%02d</p>"
           "<p>Your current IP address is %s</p>"
           "</main></body></html>",
           currentTime->tm_year + 1900, // tm_year is years since 1900
           currentTime->tm_mon + 1,    // tm_mon is months since January (0-11)
           currentTime->tm_mday,       // tm_mday is day of the month (1-31)
           currentTime->tm_hour,
           currentTime->tm_min,
           currentTime->tm_sec,
           ip);
        

    return 0;
}
