#include "../include/bsp.h"

void close_bsp(t_bspnode *node)
{
    if (!node)
    {
        if (node->side[0] != NULL || node->side[1] != NULL)
            (node->side[0] == NULL) ? close_bsp(node->side[1])
            : close_bsp(node->side[0]);
        bzero(node, sizeof(t_bspnode));
        free(node);
    }
}

/*
void close_bsp(t_bspnode *node)
{
    if (!node)
    {
        if (node->side[0] == NULL && node->side[1] == NULL)
        {
            bzero(node, sizeof(t_bspnode));
            free(node);
        }
        else
            (node->side[0] == NULL) ? close_bsp(node->side[1])
            : close_bsp(node->side[0]);
    }
}
*/
