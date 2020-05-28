#include "test.h"

void    make_divlinefromworld(t_divline *dvl, t_line *l)
{
    dvl->p = l->p1;
    dvl->dx = l->p2.x - l->p1.x;
    dvl->dy = l->p2.y - l->p1.y;
}

float    equation_plan(t_divline *v1, t_divline *v2)
{
    return ((v1->p.x - v2->p.x) * v1->dy + (v2->p.y - v1->p.y) * v1->dx);
}

float    cross_plan(t_divline *v1, t_divline *v2)
{
    return ((v1->dy * v2->dx) - (v1->dx * v2->dy));
}

float    norm_plan(t_divline *v)
{
    return (sqrt(v->dx * v->dx + v->dy * v->dy));
}

float 	intersectvector(t_divline *v2, t_divline *v1)
{
    float	frac;
	float	cross;

	cross = cross_plan(v1, v2);
	if (cross == 0)
		return (0);
	frac = equation_plan(v1, v2) / cross;
	if (frac <= 0.0 || frac >= 1.0)
		return (0);
	return (frac);
}
