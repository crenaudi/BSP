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

float	add_angle4vector(float x, float y, t_player *pl)
{
	float 	angle;
	float	angle2;
	float 	dx;
	float 	dy;
	t_vecf2	fvec;

	fvec.x = x - pl->x;
	fvec.y = y - pl->y;
	dy = cosf(pl->eyes_dirx);
	dx = sinf(pl->eyes_dirx);
	angle = atan2f(dy, dx) - atan2f(fvec.y, fvec.x);
    if (angle < -M_PI)
        angle += 2 * M_PI;
    if (angle > M_PI)
        angle -= 2 * M_PI;
	printf("test = %f\n", rad2deg(angle));
	//angle = -(M_PI / 4.) + atan2f(y, x) - (2 * M_PI);
	printf("x %f y %f\n", x, y);
	angle = atan2f(y, x);
	angle2 = atan2f(pl->y, pl->x);
	printf("atan2f line = %f\n", rad2deg(angle));
	printf("atan2f player = %f\n", rad2deg(angle2));
	angle = -M_PI / 2 + angle;
	printf("pi 3/4 %f angle %f\n", rad2deg(-M_PI/4), rad2deg(angle));
	if (angle < -M_PI / 2)
		angle += 2 * M_PI;
	if (angle < 0 && angle > -M_PI / 2)
		angle *= -1;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	printf("angle %f\n", rad2deg(angle));
	return (angle);
}

/*
float	add_angle4vector(float x, float y)
{
	float 	angle;

	//angle = -(M_PI / 4.) + atan2f(y, x) - (2 * M_PI);
	printf("x %f y %f\n", x, y);
	angle = atan2f(y, x);
	printf("atan2f == %f %f\n", angle, rad2deg(angle));
	//angle -= M_PI / 4.;
	//printf("rad %f degres %f\n", angle, rad2deg(angle));
	//angle -= deg2rad(30.);
	//printf("rad %f degres %f\n", angle, rad2deg(angle));
	if (angle < -M_PI)
		angle += 2 * M_PI;
	if (angle > M_PI)
		angle -= 2 * M_PI;
	printf("rad %f degres %f\n", angle, rad2deg(angle));
	return (angle);
}*/
