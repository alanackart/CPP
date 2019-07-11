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
 
int ABCD(int idx) {
    printf("ABCD was called, idx=%d\n", idx);
    switch(idx){
    case 1:
        printf("ABCD, case %d\n", idx);
        break;
    case 2:
        printf("ABCD, case %d\n", idx);
        break;
    default:
        printf("ABCD, case idx not defined\n");
        
    }   
    return 0;
}
 
int BCDE(int x, int y)
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
    DATA ds2 = {.x=3, .y=4}; 
    printf("x=%d, y=%d\n", ds.x, ds.y);
    /*RegFun(Min);
    Plat(&ds);
 
    RegFun(Max);
    Plat(&ds);
    */ 
    ABCD(1);
    return 0;
}
