#include "test.h"

void print_bsp(t_bspnode *bsp)
{
    t_bspnode *tmp;
    int i;

printf("\nPRINT BSP :\n\n");
    i = 1;
    tmp = bsp;
    while (tmp != NULL)
    {
        printf("node %d :\n", i);
        printf("segment %d (%f,%f)(%f,%f) :\n", tmp->line.linedef, tmp->line.p1.x,
            tmp->line.p1.y, tmp->line.p2.x, tmp->line.p2.y);
        if (tmp->side[0] != NULL)
            printf("front %d (%f,%f)(%f,%f) :\n", tmp->side[0]->line.linedef,
                tmp->side[0]->line.p1.x, tmp->side[0]->line.p1.y,
                tmp->side[0]->line.p2.x, tmp->side[0]->line.p2.y);
        else
            printf("front NULL\n");

        if (tmp->side[0] != NULL)
            printf("back %d (%f,%f)(%f,%f) :\n", tmp->side[1]->line.linedef,
                tmp->side[1]->line.p1.x, tmp->side[1]->line.p1.y,
                tmp->side[1]->line.p2.x, tmp->side[1]->line.p2.y);
        else
            printf("back NULL\n");

        tmp = tmp->side[0];
        i++;
    }
}
