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
        return (SUCCESS);
    else
        return (ERROR);
}

static int		seg_onview(t_player *pl, t_line line, int side)
{
    printf("%d\n", side);
    if (onview(pl, line.p1.x, line.p1.y) != ERROR
        || onview(pl, line.p2.x, line.p2.y) != ERROR)
        return (SUCCESS);
    if (side == 0 && onview(pl, line.bbox[0], line.bbox[2]) != ERROR)
		return (SUCCESS);
	if (side == 1 && onview(pl, line.bbox[1], line.bbox[3]) != ERROR)
		return (SUCCESS);
	return (ERROR);
}

static void   bsp_renderer(t_player *pl, t_bspnode *node, t_vecf2 ray, float ray_angle, int i)
{
    int side;

	side = pointonside((t_vecf2){pl->coord_x, pl->coord_y}, &node->divline);
    if (i < 256)
    {
        if (seg_onview(pl, node->line, side) == SUCCESS)
        {
            printf("---> node onview %d (%f,%f)(%f,%f)\n", node->line.linedef,
                node->line.p1.x, node->line.p1.y,
                node->line.p2.x, node->line.p2.y);
        }
        if (node->side[side] !=  NULL)
            bsp_renderer(pl, node->side[side], ray, ray_angle, i);
        if (node->line.side == 0 && node->side[side ^ 1] !=  NULL)
            bsp_renderer(pl, node->side[side ^ 1], ray, ray_angle, i);
    }
}

void     ray_renderer(t_player *pl, t_bspnode *node)
{
   float ray_angle;
   t_vecf2 ray;
   int x;

   x = -1;
   while (++x < 10)
   {
       printf("\nx = %d\n", x);
       ray_angle = (float)(pl->eyes_dir - pl->cam.half_fov)
            + (float)(x) / (float)(800) * pl->cam.fov;
       ray.x = sinf(ray_angle);
       ray.y = cosf(ray_angle);
       bsp_renderer(pl, node, ray, ray_angle, 0);
   }
}
