#include "../include/bsp.h"

float		evaluate_pointonview(t_cam2d c, float x, float y)
{
	float 	angle;
	float	dist;
	t_vecf2	fvec;

	fvec.x = x - c.dvl_lr.p.x;
	fvec.y = y - c.dvl_lr.p.y;
	dist = sqrtf(fvec.x * fvec.x + fvec.y * fvec.y);
    angle = atan2f(c.dvl_lr.dy, c.dvl_lr.dx) - atan2f(fvec.y, fvec.x);
    if (angle < -M_PI)
        angle += 2 * M_PI;
    if (angle > M_PI)
        angle -= 2 * M_PI;
	if (fabs(angle) < c.half_fov && dist >= 0.5f && dist < c.depth)
		return (angle);
    else
        return (0);
}
