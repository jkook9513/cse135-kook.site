#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    const char *ip = getenv("REMOTE_ADDR");
    if (!ip) ip = "unknown";

    time_t t = time(NULL);
    struct tm *currentTime = localtime(&t);


    printf("Content-Type: application/json\r\n\r\n");
    printf("{\n\"title\":\"Hello, C!\",\n"
           "\"message\":\"Hello World from Team Kook! This page was generated with the C programming language\",\n"
           "\"date\":\"%04d-%02d-%02d %02d:%02d:%02d\",\n"
           "\"currentIP\":\"%s\"\n}",
           currentTime->tm_year + 1900, // tm_year is years since 1900
           currentTime->tm_mon + 1,    // tm_mon is months since January (0-11)
           currentTime->tm_mday,       // tm_mday is day of the month (1-31)
           currentTime->tm_hour,
           currentTime->tm_min,
           currentTime->tm_sec,
           ip);

    return 0;
}
