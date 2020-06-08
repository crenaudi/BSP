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

}
