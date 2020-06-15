#include "../include/bsp-v1.h"

static float		onview(t_player *pl, float x, float y)
{
    float   dx;
    float   dy;
	float 	angle;

    dx = sinf(pl->eyes_dir);
   	dy = cosf(pl->eyes_dir);
    //printf("x : %f\ny : %f\n", x, y);
    //printf("dx : %f\ndy : %f\n", dx, dy);
    angle = atan2f(dy, dx) - atan2f(y, x);
    //printf("angle : %f\n", angle);
    if (angle < -API)
        angle += TWOPI;
    if (angle > API)
        angle -= TWOPI;
    //printf("angle : %f\n", angle);
    //printf("fabs angle : %f\n", fabs(angle));
    //printf("half fov : %f\n\n", pl->cam.half_fov);
    if (fabs(angle) < pl->cam.half_fov)
        return (angle);
    else
        return (ERROR);
}

static int		seg_onview(t_player *pl, t_line line, int side)
{
    if (onview(pl, line.p2.x, line.p2.y) != ERROR)
    {
        printf("%f %f\n", line.p2.x, line.p2.y);
        return (SUCCESS);
    }
    if (onview(pl, line.p1.x, line.p1.y) != ERROR)
    {
        printf("%f %f\n", line.p1.x, line.p1.y);
        return (SUCCESS);
    }
    if (side == 0 && onview(pl, line.bbox[0], line.bbox[2]) != ERROR)
    {
        printf("%f %f\n", line.bbox[0], line.bbox[2]);
        return (SUCCESS);
    }
	if (side == 1 && onview(pl, line.bbox[1], line.bbox[3]) != ERROR)
    {
        printf("%f %f\n", line.bbox[1], line.bbox[3]);
        return (SUCCESS);
    }
	return (ERROR);
}

static void renderer(t_bspnode *node, t_player *pl, int i, int front)
{
    int side;

    side = pointonside((t_vecf2){pl->coord_x, pl->coord_y}, &node->divline);
    if (node->side[side] != NULL && i < 256)
    {
        renderer(node->side[side], pl, i, 0);
    }
    if (seg_onview(pl, node->line, side) == SUCCESS)
    {
        printf("--> node line %d is onview\n", node->line.linedef);
        i++;
    }
    if (node->side[side ^ 1] != NULL && i < 256)
    {
        renderer(node->side[side ^ 1], pl, i, 1);
    }
}

void    bsp_renderer(t_player *pl, t_bspnode *node)
{
    t_bspnode   *tmp;
	int			i;

	tmp = node;
    printf("player : %f %f %f\n", pl->eyes_dir, pl->coord_x, pl->coord_y);
    onview(pl, 20.f, 50.f);
    onview(pl, 50.f, 70.f);
    renderer(tmp, pl, 0, 1);
}
