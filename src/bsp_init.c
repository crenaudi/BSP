#include "../include/bsp.h"

void        init_lstline(t_lst_line *lines)
{
    lines->count = 0;
    memset(&lines->lst, 256, sizeof(t_line));
}

void        init_2lstline(t_lst_line *lst1, t_lst_line *lst2)
{
    lst1->count = 0;
    memset(&lst1->lst, 256, sizeof(t_line));
    lst2->count = 0;
    memset(&lst2->lst, 256, sizeof(t_line));
}

t_bspnode   *init_node()
{
    t_bspnode *node;

    if (!(node = malloc(sizeof(*node))))
        printf("ERROR MALLOC\n");
	memset(node, 0, sizeof(*node));
    return (node);
}
