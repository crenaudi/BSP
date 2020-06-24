#include "../include/bsp.h"

void cpyl(t_line *dest, t_line *src)
{
    dest->p1 = src->p1;
    dest->p2 = src->p2;
    dest->twoside = src->twoside;
    dest->offset = src->offset;
    dest->linedef = src->linedef;
    dest->angle1 = src->angle1;
    dest->angle2 = src->angle2;
    /*
    dest->bbox[BOXLEFT] = (src->p1.x < src->p2.x) ? src->p1.x : src->p2.x;
    dest->bbox[BOXRIGHT] = (src->p1.x < src->p2.x) ? src->p2.x : src->p1.x;
    dest->bbox[BOXBOTTOM] = (src->p1.y > src->p2.y) ? src->p1.y : src->p2.y;
    dest->bbox[BOXTOP] = (src->p1.y > src->p2.y) ? src->p2.y : src->p1.y;
    */
}

t_bspnode   *bspbuild(t_lst_line *lines)
{
    t_line      bestl;
    t_lst_line  front_back[2];
    t_bspnode   *node;
    int         v[2];
    int         i;

    v[1] = INT_MAX;
    i = -1;
    bestl = lines->lst[0];
    while (++i < lines->count)
    {
        v[0] = evaluate_split(lines, &lines->lst[i], v[1], 0);
        if (v[0] < v[1] && (v[1] = v[0]))
            bestl = lines->lst[i];
    }
    node = init_node();
    cpyl(&node->line, &bestl);
    if(v[1] == INT_MAX && lines->count < 2)
        return(node);
    make_divline(&node->divline, bestl.p1, bestl.p2);
    init_2lstline(&front_back[0], &front_back[1]);
    execute_split(lines, &bestl, &front_back[0], &front_back[1]);
    node->side[0] = bspbuild(&front_back[0]);
	node->side[1] = bspbuild(&front_back[1]);
	return (node);
}
