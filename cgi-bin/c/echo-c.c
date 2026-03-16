#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static void jesc(const char *s){
  for(; *s; s++){
    unsigned char c=(unsigned char)*s;
    if(c=='\\') fputs("\\\\",stdout);
    else if(c=='"') fputs("\\\"",stdout);
    else if(c=='\n') fputs("\\n",stdout);
    else if(c=='\r') fputs("\\r",stdout);
    else if(c=='\t') fputs("\\t",stdout);
    else if(c<0x20) printf("\\u%04x",c);
    else fputc(c,stdout);
  }
}

static char *read_body(void){
  const char *cl=getenv("CONTENT_LENGTH");
  long n=cl?strtol(cl,NULL,10):0;
  if(n<=0) return strdup("");
  char *buf=(char*)malloc((size_t)n+1);
  size_t r=fread(buf,1,(size_t)n,stdin);
  buf[r]='\0';
  return buf;
}

int main(void){
  const char *method=getenv("REQUEST_METHOD"); if(!method) method="GET";
  const char *ct=getenv("CONTENT_TYPE"); if(!ct) ct="";
  const char *ip=getenv("REMOTE_ADDR"); if(!ip) ip="unknown";
  const char *ua=getenv("HTTP_USER_AGENT"); if(!ua) ua="unknown";
  const char *qs=getenv("QUERY_STRING"); if(!qs) qs="";

  char host[256]; if(gethostname(host,sizeof(host))!=0) strcpy(host,"unknown");
  time_t now=time(NULL);

  char *raw=read_body();

  printf("Content-Type: application/json\r\n\r\n");
  printf("{\"language\":\"c\",\"hostname\":\""); jesc(host);
  printf("\",\"time\":%ld,\"ip\":\""); jesc(ip);
  printf("\",\"user_agent\":\""); jesc(ua);
  printf("\",\"method\":\""); jesc(method);
  printf("\",\"content_type\":\""); jesc(ct);
  printf("\",\"query_string\":\""); jesc(qs);
  printf("\",\"raw\":\""); jesc(raw);
  printf("\"}\n");

  free(raw);
  return 0;
}
