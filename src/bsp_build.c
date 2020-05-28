#include "test.h"

void cpy_line(t_line *dest, t_line *src)
{
    /*
    if (!(dest = (t_line *)malloc(sizeof(t_line))))
        printf("ERROR MALLOC\n");
        */
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

t_bspnode   *bspbuild(t_lst_line *lines, int *cuts)
{
    t_line      line_p;
    t_line      bestline_p;
    t_lst_line  front;
    t_lst_line  back;
    int         v[2];
    t_bspnode   *node_p;
    //int         bestv, v;
    int         i;

    v[1] = INT_MAX;
    i = -1;
    while (++i < lines->count)
    {
        line_p = lines->lst[i];
        v[0] = evaluate_split(lines, &line_p, v[1], 0);
        if (v[0] < v[1])
        {
            v[1] = v[0];
            bestline_p = line_p;
        }
    }
    node_p = malloc (sizeof(*node_p));
	memset (node_p, 0, sizeof(*node_p));
    if (v[1] == INT_MAX)
    {
        //node_p->line = lines->lst[0];
        cpy_line(&node_p->line, &bestline_p);
        return(node_p);
    }
    make_divlinefromworld(&node_p->divline, &bestline_p);
    init_lstline(&front);
    init_lstline(&back);
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
        lines->lst[i].linedef = i;
        lines->lst[i].side = 0;
        lines->lst[i].offset = 0;
		lines->lst[i].grouped = false;
        if (origine[i].flags & TWOSIDED)
        {
            lines->lst[i].p1 = origine[i].p2;
            lines->lst[i].p2 = origine[i].p1;
            lines->lst[i].linedef = i;
            lines->lst[i].side = 1;
            lines->lst[i].offset = 0;
    		lines->lst[i].grouped = false;

        }
        printf("%d / %d p1(%f,%f) p2(%f,%f) side = %d\n", i, count, lines->lst[i].p1.x, lines->lst[i].p1.y,
            lines->lst[i].p2.x, lines->lst[i].p2.y, lines->lst[i].side);
    }
    /*
    if (lst[0] == NULL)
        return (NULL);
    */
}


void make_bsp(t_polygon lst_p[256], int nseg)
{
    t_lst_line  lines;
    int         cuts;
    t_bspnode   *node;

    cuts = 0;

    printf("\nBUILD BSP :\n\n" );
    make_seg(&lines, lst_p, nseg);
    lines.count = nseg;
    //check lines;
    node = bspbuild(&lines, &cuts);
    print_bsp(node);
}