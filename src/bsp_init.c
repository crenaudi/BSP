#include "../include/bsp.h"

t_map		init_map(t_engine *e, t_lst_line *polygons, int nb_sectors)
{
	t_map      	mp;
	t_bspnode	*bsp;

	bsp = bspbuild(polygons);
	if (bsp == NULL)
		doom_error(e, 0 ^ (1 << 16), "BSP fail");
	mp.nb_sectors = nb_sectors;
    mp.bsp = bsp;
	return (mp);
}

void        init_lstline(t_lst_line *lines)
{
    lines->count = 0;
    memset(&lines->lst, 256, sizeof(t_line));
	memset(&lines->leq, 256, sizeof(t_linear_eq));
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

void    add_polygon2list(t_lst_line *lines, t_vecf3 p1, t_vecf3 p2, int flags, int sector)
{
    if (lines->count < 255)
    {
        lines->lst[lines->count].p1 = p1;
        lines->lst[lines->count].p2 = p2;
        lines->lst[lines->count].linedef = lines->count + 1;
        lines->lst[lines->count].twoside = 0;
        lines->lst[lines->count].offset = 0;
        lines->lst[lines->count].sector = sector;
        if (flags & TWOSIDED)
        {
            lines->lst[lines->count].p1 = p2;
            lines->lst[lines->count].p2 = p1;
            lines->lst[lines->count].twoside = 1;
        }
        printf("line %d (%f,%f)(%f,%f)\n", lines->lst[lines->count].linedef,
            lines->lst[lines->count].p1.x, lines->lst[lines->count].p1.y,
            lines->lst[lines->count].p2.x, lines->lst[lines->count].p2.y);
        lines->count++;
    }
    else
        printf("trop de polygonnes\n");
}
