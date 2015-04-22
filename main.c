
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "heap.h"

int main()
{
    char *t = (char*)malloc(100000);

    SetMemory(t, t+8000);

    int val = 5;
    char *p1, *p2, *p3, *p4, *p5, *p6;
    p1 = MemLoc(val);
    printf("%p p1 \n", p1);

    p2 = MemLoc(val);
    printf("%p p2 \n", p2);

    p3 = MemLoc(val);
    printf("%p p3 \n", p3);

    p4 = MemLoc(val);
    printf("%p p4 \n", p4);

    FreeMem(p1);
    FreeMem(p2);
    FreeMem(p3);

    p5 = MemLoc(val*3);
    printf("%p p5 \n", p5);

    p6 = MemLoc(val);
    printf("%p p6 \n", p6);

    //FreeMem(p5);

    printf("\n\n");
    MapMemory();
    free(t);

    printf("\n\n");
    return 0;
}
