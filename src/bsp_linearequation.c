#include "../include/bsp.h"

void precompute_linear_equation(t_linear_eq *leq, float plx, float ply)
{
	float a;
	float plan;
	float b;
	float px;
	float py;
	float divxy;
	float divyy;

	printf("player : %f, %f\n", plx, ply);
	printf("p : %f, %f\n", leq->p.x, leq->p.y);
	printf("dx : %f\n", leq->dx);
	printf("dy : %f\n", leq->dy);
	a = leq->dy / leq->dx;
	b = leq->p.y - (a * leq->p.x);
	plan = b * leq->dx;
	px = plx * leq->dx;
	py = ply * leq->dx;
	plan = py - plan;
    leq->xprime.x = plan - px;
    leq->xprime.y = leq->dy - leq->dx;
    divxy = leq->dx / leq->dy;
	divyy = leq->dy / leq->dy;
	plan = (plan / leq->dx);
	plan = plan + (b * divyy);
    leq->yprime.x = plan - ((px / leq->dx) + (b * divxy));
    leq->yprime.y = (divyy - divxy);
}

void execute_linear_equation(t_linear_eq *leq, float plx, float ply, float a)
{
	float x;
    float y;

	printf("angle : %f -> %f\n",a, rad2deg(a));
	leq->pprime.x = leq->xprime.x * tanf(a) / leq->xprime.y * tanf(a);
	leq->pprime.y = leq->yprime.x * tanf(a) / leq->yprime.y * tanf(a);
	printf("P' : %f, %f\n", leq->pprime.x, leq->pprime.y);
    x = leq->pprime.x - plx;
    y = leq->pprime.y - ply;
	leq->dist = sqrtf(x * x + y * y);
}
/*
    d = leq->d;
	a = d->dy / d->dx;
	plan = d->p.y - (a * d->p.x);
	b = ply - (plx * tanf(a));

	y' = x' * tan(angle) + b
	a * x' + plan = x' * tan(angle) + b;
	x' * d->dy + (plan * d->dx) = (x * d->dx) * tan(angle) + (p.y * d->dx) - (p.x * d->dx) * tan(angle);
	x' * d->dy - (x' * d->dx) * tan(angle) = ((plan * d->dx) - (p.y * d->dx)) - (p.x * d->dx) * tan(angle);
    x' - (x' * d->dx) * tan(angle) = (plan - py) - px * tan(angle);
    x' =  (plan - px) * tan(angle) / (dy - dx) * tan(angle);

	plan *= d->dx;
	px = p.x * d->dx;
	py = p.y * d->dx;
	plan = py - plan;
    leq->xprime.x = (plan - px);
    leq->xprime.y = (dy - dx);

	y' = a * x' + b;
	y' = (dy / dx) * (x') +  p.y - (p.x * tan(angle));
	y' = (dy / dx) * (plan - px * tan(angle) / (dy - dx) * tan(angle)) +  p.y - (p.x * tan(angle));
	y' = (plan / dx) - (px / dx) * tan(angle) +  (b * (dy / dy)) - (b * (dx / dy)) * tan(angle);
		___________________________________   ________________________________________________
		((dy / dy) - (dx / dy)) * tan(angle)   (1 * (dy / dy) - 1 * (dx / dy)) * tan(angle)

	divxy = d->dx / d->dy;
	divyy = d->dy / d->dy;
	plan = (plan / d->dx) + b * divyy;
	b *= divxy;
    leq->yprime.x = (plan - ((px / d->dx) + b));
    leq->yprime.y = (divyy - divxy);
	y' = (plan - ((px / d->dx) + b)) * tan(angle) / (divyy - divxy) * tan(angle);
*/
/*
void execute_linear_equation(t_linear_eq *leq, float plx, float ply, float a)
{
	float x;
    float y;

	leq->pprime.x = leq->xprime.x * tanf(a) / leq->xpirme.y * tanf(a);
	leq->pprime.y = leq->yprime.x * tanf(a) / leq->yprime.y * tanf(a);
    x = leq->pprime.x - plx;
    y = leq->pprime.y - ply;
	leq->dist = sqrtf(x * x + y * y);
}
*/
