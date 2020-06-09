#include "../include/bsp.h"

void cpy_line(t_line *dest, t_line *src)
{
    dest->p1 = src->p1;
    dest->p2 = src->p2;
    dest->side = src->side;
    dest->offset = src->offset;
    dest->linedef = src->linedef;
    dest->grouped = src->grouped;
}
static void        init_lstline(t_lst_line *lines)
{
    lines->count = 0;
    memset(&lines->lst, 256, sizeof(t_line));
}

t_bspnode   *bspbuild(t_lst_line *lines, t_vecf2 pt, int *cuts)
{
    t_line      bestline;
    t_lst_line  front;
    t_lst_line  back;
    t_bspnode   *node_p;
    int         i;

    if (lines->count == 0)
        return (NULL);
    bestline = evaluate_closer(lines, INT_MAX, pt);

    printf("\nbestline_p %d (%f,%f)(%f,%f)\n\n", bestline.linedef,
        bestline.p1.x, bestline.p1.y, bestline.p2.x, bestline.p2.y);

    node_p = malloc (sizeof(*node_p));
	memset (node_p, 0, sizeof(*node_p));
    if (lines->count < 2)
    {
        cpy_line(&node_p->line, &bestline);
        return(node_p);
    }
    make_divlinefromworld(&node_p->divline, &bestline);
    init_lstline(&front);
    init_lstline(&back);
    cpy_line(&node_p->line, &bestline);
    execute_split(lines, &bestline, &front, &back, cuts);
    node_p->side[0] = bspbuild(&front, point_closer2seg(bestline.p1, bestline.p2, pt), cuts);
	node_p->side[1] = bspbuild(&back, point_closer2seg(bestline.p1, bestline.p2, pt), cuts);

	return (node_p);
}

void    make_seg(t_lst_line *lines, t_polygon origine[256], int nseg)
{
    int     count;
    int     i;

    count = nseg;
    i = -1;
    while (++i < count)
    {
        lines->lst[i].p1 = origine[i].p1;
        lines->lst[i].p2 = origine[i].p2;
        lines->lst[i].linedef = i + 1;
        lines->lst[i].side = 0;
        lines->lst[i].offset = 0;
        lines->lst[i].sector = origine[i].sector;
		lines->lst[i].grouped = false;
        if (origine[i].flags & TWOSIDED)
        {
            lines->lst[i].p1 = origine[i].p2;
            lines->lst[i].p2 = origine[i].p1;
            lines->lst[i].side = 1;
        }
        printf("line %d (%f,%f)(%f,%f)\n", lines->lst[i].linedef,
            lines->lst[i].p1.x, lines->lst[i].p1.y,
            lines->lst[i].p2.x, lines->lst[i].p2.y);
    }
}

t_bspnode   *make_bsp(t_polygon lst_p[256], int nseg, t_vecf2 pl_pos)
{
    t_lst_line  lines;
    int         cuts;
    t_bspnode   *node;

    cuts = 0;

    make_seg(&lines, lst_p, nseg);
    printf("pl (%f,%f)\n", pl_pos.x, pl_pos.y);
    lines.count = nseg;
    node = bspbuild(&lines, pl_pos, &cuts);
    printf("build ok\n");
    print_bsp(node);
    printf("print ok\n");
    close_bsp(node);
    printf("close ok\n");
    return (NULL);
}
/*
printf("%d / %d p1(%f,%f) p2(%f,%f) side = %d\n", lines->lst[i].linedef, count, lines->lst[i].p1.x, lines->lst[i].p1.y,
    lines->lst[i].p2.x, lines->lst[i].p2.y, lines->lst[i].side);
    printf("bestline_p %d (%f,%f)(%f,%f)\n", bestline_p.linedef,
        bestline_p.p1.x, bestline_p.p1.y, bestline_p.p2.x, bestline_p.p2.y);
*/
