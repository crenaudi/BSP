#include "../../include/bsp.h"

void cpy_line(t_line *dest, t_line *src)
{
    dest->p1 = src->p1;
    dest->p2 = src->p2;
    dest->side = src->side;
    dest->offset = src->offset;
    dest->linedef = src->linedef;
    dest->grouped = src->grouped;
    if (src->p1.x < src->p2.x)
    {
        dest->bbox[0] = src->p1.x;
        dest->bbox[1] = src->p2.x;
    }
    else
    {
        dest->bbox[0] = src->p2.x;
        dest->bbox[1] = src->p1.x;
    }
    if (src->p1.y > src->p2.y)
    {
        dest->bbox[2] = src->p1.y;
        dest->bbox[3] = src->p2.y;
    }
    else
    {
        dest->bbox[2] = src->p2.y;
        dest->bbox[3] = src->p1.y;
    }
    //left, right, top, bottom;
}

static void        init_lstline(t_lst_line *lines)
{
    lines->count = 0;
    memset(&lines->lst, 256, sizeof(t_line));
}

t_bspnode   *bspbuild(t_lst_line *lines, int *cuts)
{
    t_line      line_p;
    t_line      bestline_p;
    t_lst_line  front;
    t_lst_line  back;
    int         v[2];
    t_bspnode   *node_p;
    int         i;

    v[1] = INT_MAX;
    i = -1;
    if (lines->count == 0)
        return (NULL);
    bestline_p = lines->lst[0];
    while (++i < lines->count)
    {
        line_p = lines->lst[i];
        printf("line_p %d (%f,%f)(%f,%f)\n", line_p.linedef,
                line_p.p1.x, line_p.p1.y, line_p.p2.x, line_p.p2.y);
        v[0] = evaluate_split(lines, &line_p, v[1], 0);
        if (v[0] < v[1])
        {
            v[1] = v[0];
            bestline_p = line_p;
        }
    }
    printf("\nbestline_p %d (%f,%f)(%f,%f)\n\n", bestline_p.linedef,
        bestline_p.p1.x, bestline_p.p1.y, bestline_p.p2.x, bestline_p.p2.y);
    node_p = malloc (sizeof(*node_p));
	memset (node_p, 0, sizeof(*node_p));
    if (v[1] == INT_MAX && lines->count < 2)
    {
        cpy_line(&node_p->line, &line_p);
        return(node_p);
    }
    make_divlinefromworld(&node_p->divline, &bestline_p);
    init_lstline(&front);
    init_lstline(&back);
    cpy_line(&node_p->line, &bestline_p);
    execute_split(lines, &bestline_p, &front, &back, cuts);
    node_p->side[0] = bspbuild(&front, cuts);
	node_p->side[1] = bspbuild(&back, cuts);

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

t_bspnode   *make_bsp(t_polygon lst_p[256], int nseg)
{
    t_lst_line  lines;
    int         cuts;
    t_bspnode   *node;

    cuts = 0;

    make_seg(&lines, lst_p, nseg);
    printf("ok\n");
    lines.count = nseg;
    node = bspbuild(&lines, &cuts);
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
