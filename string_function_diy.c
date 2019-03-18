#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strrev_diy(char *dest, const char *src)
{
    int len = strlen(src);
    char *p = dest + len;
    *p = '\0'; // null terminate
    p = p-1;
    while(*src != '\0')
    {
        *(p) = *(src++);
        //printf("%c ",   *(p) );
        p--;
    }
    return dest;
}

int main()
{
    char str2[] = "Hello#world!";
    char str[20];
    strrev_diy(str, str2);
    printf("strrev of str2=%s\n", str);
    return 0;
}
