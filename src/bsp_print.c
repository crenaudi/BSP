#include "../include/bsp.h"

void print_bsp(t_bspnode *bsp)
{
    t_bspnode *tmp1;
    t_bspnode *tmp2;

    printf("\nPRINT BSP :\n\n");
    tmp1 = bsp;
    printf("node :\n\n");
    printf("segment %d (%f,%f)(%f,%f) :\n", tmp1->line.linedef, tmp1->line.p1.x,
        tmp1->line.p1.y, tmp1->line.p2.x, tmp1->line.p2.y);
    if (tmp1->side[0] != NULL)
        printf("front %d (%f,%f)(%f,%f) :\n", tmp1->side[0]->line.linedef,
        tmp1->side[0]->line.p1.x, tmp1->side[0]->line.p1.y,
        tmp1->side[0]->line.p2.x, tmp1->side[0]->line.p2.y);
    else
        printf("front NULL\n");

    if (tmp1->side[0] != NULL)
        printf("back %d (%f,%f)(%f,%f) :\n", tmp1->side[1]->line.linedef,
            tmp1->side[1]->line.p1.x, tmp1->side[1]->line.p1.y,
            tmp1->side[1]->line.p2.x, tmp1->side[1]->line.p2.y);
    else
        printf("back NULL\n");

    tmp1 = tmp1->side[0];
    tmp2 = tmp1->side[1];

    printf("\n\nfront node :\n\n");
    printf("segment %d (%f,%f)(%f,%f) :\n", tmp1->line.linedef, tmp1->line.p1.x,
        tmp1->line.p1.y, tmp1->line.p2.x, tmp1->line.p2.y);
    if (tmp1->side[0] != NULL)
        printf("front %d (%f,%f)(%f,%f) :\n", tmp1->side[0]->line.linedef,
        tmp1->side[0]->line.p1.x, tmp1->side[0]->line.p1.y,
        tmp1->side[0]->line.p2.x, tmp1->side[0]->line.p2.y);
    else
        printf("front NULL\n");

    if (tmp1->side[0] != NULL)
        printf("back %d (%f,%f)(%f,%f) :\n", tmp1->side[1]->line.linedef,
            tmp1->side[1]->line.p1.x, tmp1->side[1]->line.p1.y,
            tmp1->side[1]->line.p2.x, tmp1->side[1]->line.p2.y);
    else
        printf("back NULL\n");


    printf("\n\nback node :\n\n");
    printf("segment %d (%f,%f)(%f,%f) :\n", tmp2->line.linedef, tmp2->line.p1.x,
        tmp2->line.p1.y, tmp2->line.p2.x, tmp2->line.p2.y);
    if (tmp2->side[0] != NULL)
        printf("front %d (%f,%f)(%f,%f) :\n", tmp2->side[0]->line.linedef,
        tmp2->side[0]->line.p1.x, tmp2->side[0]->line.p1.y,
    tmp2->side[0]->line.p2.x, tmp2->side[0]->line.p2.y);
    else
        printf("front NULL\n");
    if (tmp2->side[0] != NULL)
        printf("back %d (%f,%f)(%f,%f) :\n", tmp2->side[1]->line.linedef,
            tmp2->side[1]->line.p1.x, tmp2->side[1]->line.p1.y,
            tmp2->side[1]->line.p2.x, tmp2->side[1]->line.p2.y);
    else
        printf("back NULL\n");
}
