#include "../include/bsp.h"

static int		onview(t_player *pl, float x, float y)
{
    float   dx;
    float   dy;
	float 	angle;

    printf("%f %f %f\n", pl->eyes_dir, x, y);
    dx = sinf(pl->eyes_dir);
   	dy = cosf(pl->eyes_dir);
    angle = atan2f(dy, dx) - atan2f(y, x);
    if (angle < -API)
        angle += TWOPI;
    if (angle > API)
        angle -= TWOPI;
    if (fabs(angle) < pl->cam.half_fov)
        return (SUCCESS);
    else
        return (ERROR);
}

static int		seg_onview(t_player *pl, float bbox[4])
{
	if (onview(pl, bbox[1], bbox[2]) != ERROR
        || onview(pl, bbox[0], bbox[3]) != ERROR
        || onview(pl, bbox[0], bbox[2]) != ERROR
        || onview(pl, bbox[1], bbox[3]) != ERROR)
		return (SUCCESS);
	return (ERROR);
}

static void   render_lstlines(t_lst_line *plines, t_bspnode *node, t_player *pl)
{
    int side;

    side = pointonside((t_vecf2){pl->coord_x, pl->coord_y}, &node->divline);
    printf("node %d bbox(%f,%f,%f,%f)\n", node->line.linedef, node->bbox[0], node->bbox[1], node->bbox[2], node->bbox[3]);
    if (plines->count < 256)
    {
        if (seg_onview(pl, node->line.bbox) == SUCCESS)
        {
            printf("---> node onview %d bbox(%f,%f,%f,%f)\n", node->line.linedef, node->bbox[0], node->bbox[1], node->bbox[2], node->bbox[3]);
            cpy_line(&plines->lst[plines->count], &node->line);
            plines->count++;
            if (node->line.side == 1)
                side = 1;
        }
        if (node->side[side] !=  NULL )
            render_lstlines(plines, node->side[side], pl);
        if (node->side[side ^ 1] !=  NULL)
            render_lstlines(plines, node->side[side ^ 1], pl);
    }
}

void    bsp_renderer(t_player *pl, t_bspnode *node)
{
    t_lst_line  plines;
    t_bspnode   *tmp;
	int			i;

	tmp = node;
    plines.count = 0;
    printf("\nFind lines :\n\n" );
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
