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

	a = leq->dy / leq->dx;
	b = leq->p.y - (a * leq->p.x);
	plan = b * leq->dx;
	px = plx * leq->dx;
	py = ply * leq->dx;
	plan = py - plan;
    //leq->xprime.a = plan - px;
    //leq->xprime.b = leq->dy - leq->dx;

	leq->xprime.x = plan;
    leq->xprime.y = px;
	leq->xprime.z = leq->dy;
	leq->xprime.w = leq->dx;

    divxy = leq->dx / leq->dy;
	divyy = leq->dy / leq->dy;
	plan = (plan / leq->dx);
	plan = plan + (b * divyy);

    //leq->yprime.x = plan - ((px / leq->dx) + (b * divxy));
    //leq->yprime.y = (divyy - divxy);
	leq->yprime.x = plan;
    leq->yprime.y = (px / leq->dx) + (b * divxy);
	leq->yprime.z = divyy;
    leq->yprime.w = divxy;
}

void execute_linear_equation(t_linear_eq *leq, float plx, float ply, float a)
{
	float x;
    float y;

	leq->pprime.x = (leq->xprime.x - (leq->xprime.y * tanf(a)))
		/ (leq->xprime.z - (leq->xprime.w * tanf(a)));
	leq->pprime.y = (leq->yprime.x - (leq->yprime.y * tanf(a)))
		/ (leq->yprime.z - (leq->yprime.w * tanf(a)));
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
/*
void precompute_linear_equation(t_linear_eq *leq, float plx, float ply)
{
	leq->plan = (leq->p.x - plx) * leq->dy + (ply - leq->p.y) * leq->dx;;
}

void execute_linear_equation(t_linear_eq *leq, float plx, float ply, float a)
{
	float       frac;
	float		cross;
	float 		dx;
	float 		dy;
	t_vecf2     new;
	t_vecf2     dist;

	make_divline(&seg, line->p1, line->p2);
	new.x = pl->x + sinf(angle) * pl->cam.depth;
    new.y = pl->y + cosf(angle) * pl->cam.depth;
	dx = pl->x * sinf(angle);
    dy = pl->y * cosf(angle);
	player.p = pl->cam.dvl_lr.p;
	player.dx = new.x - pl->x;
	player.dy = new.y - pl->y;
	frac = intersect_vector(&seg, &player);
	new.x = seg.p.x + float_round(seg.dx * frac);
	new.y = seg.p.y + float_round(seg.dy * frac);
	dist.x = new.x - pl->x;
	dist.y = new.y - pl->y;
	return (sqrtf(dist.x * dist.x + dist.y * dist.y));


	dx = plx * sinf(a);
    dy = ply * cosf(a);
	cross = (leq->dy * dx) - (leq->dx * dy);
	frac = leq->plan / cross;
	printf("frac : %f\n", frac);
	if (frac <= 0.0)
		frac = 0;
	if (frac >= 1.0)
		frac = 1;
	new.x = leq->p.x + float_round(leq->dx * frac);
	new.y = leq->p.y + float_round(leq->dy * frac);
	//printf("NEW = %f %f\n", new.x, new.y);
	dist.x = new.x - plx;
	dist.y = new.y - ply;
	leq->dist = sqrtf(dist.x * dist.x + dist.y * dist.y);
}
*/
