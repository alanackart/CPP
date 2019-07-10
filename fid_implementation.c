#include <stdio.h>
#include <stdlib.h>
typedef struct data{
    int x;
    int y;
}DATA;
 
int (* g_pFun) (int x, int y);
 

int Plat(DATA * d)
{
    int r;
    printf("d->x=%d, d->y=%d\n", d->x, d->y);
    r = g_pFun(d->x, d->y);
 
    printf("%d\n", r);
 
    return 0;
}
 

int RegFun(int (*pFun)(int x, int y))
{
    g_pFun = pFun;
 
    return 0;
}
 
int Max(int x, int y)
{
    if(x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}
 
int Min(int x, int y)
{
    if (x < y)
        return x;
    else
        return y;
}
 
int main(int argc, char const *argv[])
{
    /* code */
    DATA ds = {3, 4}; 
    printf("x=%d, y=%d\n", ds.x, ds.y);
    RegFun(Min);
    Plat(&ds);
 
    RegFun(Max);
    Plat(&ds);
 
    return 0;
}
