#include "../include/bsp.h"

static float		onview(t_player *pl, float x, float y)
{
    float   dx;
    float   dy;
	float 	angle;

    dx = sinf(pl->eyes_dir);
   	dy = cosf(pl->eyes_dir);
    angle = atan2f(dy, dx) - atan2f(y, x);
    if (angle < -API)
        angle += TWOPI;
    if (angle > API)
        angle -= TWOPI;
    if (fabs(angle) < pl->cam.half_fov)
        return (angle);
    else
        return (ERROR);
}

static int		seg_onview(t_player *pl, t_line line)
{
	if (onview(pl, line.p1.x, line.p1.y) != ERROR
        || onview(pl, line.p2.x, line.p2.y) != ERROR
        || onview(pl, line.bbox[0], line.bbox[2]) != ERROR
        || onview(pl, line.bbox[1], line.bbox[3]) != ERROR)
		return (SUCCESS);
	return (ERROR);
}

static void   render_lstlines(t_lst_line *plines, t_bspnode *node, t_player *pl)
{
    int first_side;
    int second_side;

	first_side = pointonside((t_vecf2){pl->coord_x, pl->coord_y}, &node->divline);
    second_side = (first_side == 0) ? 1 : 0;
    printf("node %d (%f,%f) (%f,%f)\n", node->line.linedef, node->line.p1.x,
        node->line.p1.y, node->line.p2.x, node->line.p2.y);
    if (node->line.side == 0 && plines->count < 256
        && seg_onview(pl, node->line) == SUCCESS)
    {
        cpy_line(&plines->lst[plines->count], &node->line);
        printf("line %d (%f,%f) (%f,%f)\n", plines->lst[plines->count].linedef,
			plines->lst[plines->count].p1.x, plines->lst[plines->count].p1.y,
			plines->lst[plines->count].p2.x, plines->lst[plines->count].p2.y);
        plines->count++;
        render_lstlines(plines, node->side[first_side], pl);
        render_lstlines(plines, node->side[second_side], pl);
    }
}

void    bsp_renderer(t_player *pl, t_bspnode *node)
{
    t_lst_line  plines;
    t_bspnode   *tmp;
	int			i;

	tmp = node;
    //tmp = first_visible_node(pl, tmp);
    plines.count = 0;
    render_lstlines(&plines, tmp, pl);
	printf("\nPrintable lines :\n\n" );
	i = -1;
	while (++i < plines.count)
	{
		printf("line %d (%f,%f) (%f,%f)\n", plines.lst[i].linedef,
			plines.lst[i].p1.x, plines.lst[i].p1.y,
			plines.lst[i].p2.x, plines.lst[i].p2.y);
	}
}
