#include "../include/bsp.h"

static t_vecf2		sub2vecf(t_vecf2 a, t_vecf2 b)
{
	t_vecf2 c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return (c);
}

static float		cross2vecf(t_vecf2 a, t_vecf2 b)
{
	float	c;

	c = (a.x * b.y) - (a.y * b.x);
	return (c);
}

int evaluate_intersectline(t_vecf2 x[2], t_vecf2 y[2], float tol)
{
	t_vecf2    dx;
    t_vecf2    dy;
	float      d;
    float      a;

    dx = sub2vecf(x[1], x[0]);
    dy = sub2vecf(y[1], y[0]);
	d = cross2vecf(dy, dx);
	if (!d)
        return 0; /* bords are parallel */
	a = (cross2vecf(x[0], dx) - cross2vecf(y[0], dx)) / d;
	if (a < -tol || a > 1 + tol)
        return -1;
	if (a < tol || a > 1 - tol)
        return 0;
	a = (cross2vecf(x[0], dy) - cross2vecf(y[0], dy)) / d;
	if (a < 0 || a > 1)
        return -1;
	return 1;
}
