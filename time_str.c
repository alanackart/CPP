#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
char *current_time_2()
{
    time_t        tnow;
    struct tm     *timep;
    static char   current[20];

    /*  Get current time, hh:mm */
    time(&tnow);
    timep = localtime(&tnow);
    sprintf (current, "%4d%02d%02d-%02d:%02d:%02d",
             timep->tm_year + 1900, timep->tm_mon + 1, timep->tm_mday,
             timep->tm_hour, timep->tm_min, timep->tm_sec);
    return(current);
}

char * getSub(char *str, int begin, int end){
       int i = 0;
       int j;
       static char time[10];
       for(j = begin; j <= end; j++ )
         time[i++] = str[j];
       time[i] = '\0';
       return(time);
}
struct tm* getTime(char *str){
      static struct tm* ct ;
      ct = (struct tm*)malloc(sizeof(struct tm));
      ct->tm_year = atoi(getSub(str, 0, 3));
      ct->tm_mon = atoi(getSub(str, 4, 5));
      ct->tm_mday = atoi(getSub(str, 6, 7));
      ct->tm_hour = atoi(getSub(str, 9, 10));
      ct->tm_min = atoi(getSub(str, 12, 13));
      ct->tm_sec = atoi(getSub(str, 15, 16));

      //printf( "time t: %04d%02d%02d-%02d:%02d:%02d\n", ct->tm_year, ct->tm_mon, ct->tm_mday, ct->tm_hour, ct->tm_min, ct->tm_sec);
      return ct;
}
int main(){
    /*
    char instr[120];
    time_t localnow;
    localnow = time(NULL);
    struct tm localct;

    double seconds = 0;
    char str[100]= "20190308-21:41:46";
    sscanf(str, "%04d%02d%02d-%02d:%02d:%02d", &localct.tm_year, &localct.tm_mon, &localct.tm_mday, &localct.tm_hour, &localct.tm_min, &localct.tm_sec);
    fprintf(stderr, "%04d%02d%02d-%02d:%02d:%02d\n", localct.tm_year, localct.tm_mon, localct.tm_mday, localct.tm_hour, localct.tm_min, localct.tm_sec );
    localct.tm_year = localct.tm_year - 1900;
    localct.tm_mon = localct.tm_mon - 1;
    time_t now = mktime(&localct);
    seconds = difftime(time(NULL), now);
    printf("%f\n", seconds);
    */
    char str[] = "fc_xbond.dat#100#10";
    char *p;
    p = strtok(str, "#");
    printf("p is %s\n", p);
    p = strtok(NULL, "#");
    printf("p is %s\n", p);
    p = strtok(NULL, "#");
    printf("p is %s\n", p);
    
}
