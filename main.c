
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "heap.h"

int main()
{
    char *t = (char*)malloc(100000);

    SetMemory(t, t+8000);
    int i = 0;
    for(; i<8000; ++i)
        t[i] = i;
    printf("%p t \n", t);
    int val = 5;
    char *p1, *p2, *p3, *p4, *p5, *p6;
    p1 = MemLoc(val);
    printf("%p p1 %i\n", p1, p1-t);

    p2 = MemLoc(val);
    printf("%p p2 %i\n", p2, p2-p1);

    p3 = MemLoc(val);
    printf("%p p3 %i\n", p3, p3-p2);

    p4 = MemLoc(val);
    printf("%p p4 %i\n", p4, p4-p3);

    FreeMem(p1);
    FreeMem(p2);
    FreeMem(p3);

    p5 = MemLoc(val*3);
    printf("%p p5 %i\n", p5, p5-p4);

    p6 = MemLoc(val);
    printf("%p p6 %i\n", p6, p6-p5);

    //FreeMem(p5);


    //free(t);

    MapMemory();
    printf("\n\n");
    return 0;
}
