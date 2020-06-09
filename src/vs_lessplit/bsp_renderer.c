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

static float		seg_onview(t_player *pl, t_vecf2 a, t_vecf2 b)
{
    float   mdlx;
	float   mdly;

	if (onview(pl, a.x, a.y) != ERROR || onview(pl, b.x, b.y) != ERROR)
		return (0);
	mdlx = a.x + (b.x - a.x) / 2.;
	mdly = a.y + (b.y - a.y) / 2.;
	if (onview(pl, mdlx, mdly) != ERROR)
		return (0);
	return (-1);
}

void   render_lstlines(t_lst_line *plines, t_bspnode *node, t_player *pl)
{
    int side;

	side = pointonside((t_vecf2){pl->coord_x, pl->coord_y}, &node->divline);

    if (air du polygon is visible)
        plines->count++;
        render_lstlines(plines, node[side], pl);


    if (node->line.side == 0 && plines->count < 256 /* && node->side[0] == visible && none already in list*/)
    {
		plines->count++;
        render_lstlines(plines, node->side[0], pl);
    }
	if (seg_onview(pl, node->line.p1, node->line.p2) != ERROR)
        cpy_line(&plines->lst[plines->count], &node->line);

    if (node->line.side == 0 && plines->count < 256 /* && node->side[1] == visible && none already in list*/)
    {
        plines->count++;
        render_lstlines(plines, node->side[1], pl);
    }
	if (seg_onview(pl, node->line.p1, node->line.p2) != ERROR)
        cpy_line(&plines->lst[plines->count], &node->line);
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
	printf("Printable lines :\n" );
	i = -1;
	while (++i < plines.count)
	{
		printf("line %d (%f,%f) (%f,%f)\n", plines.lst[i].linedef,
			plines.lst[i].p1.x, plines.lst[i].p1.y,
			plines.lst[i].p2.x, plines.lst[i].p2.y);
	}
}

/*
t_bspnode   *first_visible_node(t_player *pl, t_bspnode *node)
{
	int side;

    if (seg_onview(pl, node->line.p1, node->line.p2) != ERROR)
		return (node);
    else
	{
		side = pointonside((t_vecf2){pl->coord_x, pl->coord_y}, &node->divline);
		first_visible_node(pl, node->side[side]);
	}
	return (node);
}
*/
