#include "../../include/bsp.h"

void print_bsp(t_bspnode *node)
{
    if (node->side[0] != NULL || node->side[1] != NULL)
        (node->side[0] == NULL) ? print_bsp(node->side[1])
        : print_bsp(node->side[0]);
    printf("\nnode %d p1(%f,%f) p2(%f,%f)\n", node->line.linedef,
        node->line.p1.x, node->line.p1.y,
        node->line.p2.x, node->line.p2.y);
    if (node->side[0] != NULL)
        printf("    front node %d p1(%f,%f) p2(%f,%f)\n", node->line.linedef,
            node->side[0]->line.p1.x, node->side[0]->line.p1.y,
            node->side[0]->line.p2.x, node->side[0]->line.p2.y);
    if (node->side[1] != NULL)
        printf("    back node %d p1(%f,%f) p2(%f,%f)\n", node->line.linedef,
            node->side[1]->line.p1.x, node->side[1]->line.p1.y,
            node->side[1]->line.p2.x, node->side[1]->line.p2.y);
}
