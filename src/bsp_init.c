#include "../include/bsp.h"

t_map		init_map(t_engine *e, t_lstl *polygons, int nb_sectors)
{
	int			i;
	t_map      	mp;
	t_bspnode	*bsp;

	bsp = bspbuild(polygons);
	if (bsp == NULL)
		doom_error(e, 0 ^ (1 << 16), "BSP fail");
	mp.nb_sectors = nb_sectors;
    mp.bsp = bsp;
	printf("BSP OK\n");
	if (!(mp.sectors = malloc(sizeof(t_sector) * nb_sectors)))
		printf("error");
	i = -1;
	while (++i < nb_sectors)
		mp.sectors[i] = init_sector(0, 6);
	printf("sector OK\n");
	return (mp);
}

void        init_lstline(t_lstl *lines)
{
    lines->count = 0;
    memset(&lines->lst, 256, sizeof(t_line));
	memset(&lines->vx, 256, sizeof(t_vxinfo));
}

void        init_2lstline(t_lstl *lst1, t_lstl *lst2)
{
    lst1->count = 0;
    memset(&lst1->lst, 256, sizeof(t_line));
    lst2->count = 0;
    memset(&lst2->vx, 256, sizeof(t_vxinfo));
}

t_bspnode   *init_node()
{
    t_bspnode *node;

    if (!(node = malloc(sizeof(*node))))
        printf("ERROR MALLOC\n");
	memset(node, 0, sizeof(*node));
    return (node);
}

void    add_polygon2list(t_lstl *lines, t_vecf3 p1, t_vecf3 p2, int flags, int sector)
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
