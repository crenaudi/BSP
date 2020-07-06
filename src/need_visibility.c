#include "../include/bsp.h"

int		evaluate_pointonview(t_cam2d c, t_divline pl, float objx, float objy)
{
	float 	angle;
	float	dist;
	t_vecf2	fvec;

	fvec.x = objx - pl.p.x;
	fvec.y = objy - pl.p.y;
	dist = sqrtf(fvec.x * fvec.x + fvec.y * fvec.y);
    angle = atan2f(pl.dy, pl.dx) - atan2f(fvec.y, fvec.x);
    if (angle < -M_PI)
        angle += 2 * M_PI;
    if (angle > M_PI)
        angle -= 2 * M_PI;
	if (fabs(angle) < c.half_fov && dist >= 0.5f && dist < c.depth)
		return (SUCCESS);
    else
        return (ERROR);
}

float	add_angle4vector(t_cam2d c, t_divline pl, float objx, float objy)
{
	float 	angle;
	t_vecf2	fvec;

(void)c;
	fvec.x = objx - pl.p.x;
	fvec.y = objy - pl.p.y;
    angle = atan2f(pl.dy, pl.dx) - atan2f(fvec.y, fvec.x);
    if (angle < -M_PI)
        angle += 2 * M_PI;
    if (angle > M_PI)
        angle -= 2 * M_PI;
	return (angle);
}
