#include "../include/bsp.h"

static float	add_arctan(t_ray *r)
{
	t_vecf2 b;

	if (r->ray_dist.x < r->ray_dist.y)
	{
		b.x = (r->hit_x < 0) ? 1 : 0;
		b.y = r->hit_y - r->bloc_my;
	}
	else
	{
		b.x = r->hit_x - r->bloc_mx;
		b.y = (r->hit_y < 0) ? 1 : 0;
	}
	return (atan2f(b.y, b.x));
}

void			dda_info_txtur(t_ray *r, t_player *p)
{
	r->bloc_mx = (float)(r->map_x) + 0.5f;
	r->bloc_my = (float)(r->map_y) + 0.5f;
	r->hit_x = p->coord_x + r->ray.x * r->ray_dist.x;
	r->hit_y = p->coord_y + r->ray.y * r->ray_dist.y;
	r->bloc_angle = add_arctan(r);
	if (r->bloc_angle >= -API_4 && r->bloc_angle < API_4)
	{
		r->nbw = 0;
		r->tex_x = r->hit_y - (float)r->map_y;
	}
	if (r->bloc_angle >= API_4 && r->bloc_angle < API_34)
	{
		r->nbw = 1;
		r->tex_x = 1. - (r->hit_x - (float)r->map_x);
	}
	if (r->bloc_angle < -API_4 && r->bloc_angle >= -API_34)
	{
		r->nbw = 2;
		r->tex_x = r->hit_x - (float)r->map_x;
	}
	if (r->bloc_angle >= API_34 || r->bloc_angle < -API_34)
	{
		r->nbw = 3;
		r->tex_x = 1. - (r->hit_y - (float)r->map_y);
	}
}

float	dist2point(t_player *pl, t_vecf3 wall)
{
	float	x;
	float	y;

	x = wall.x - pl->x;
	y = wall.y - pl->y;
	return (sqrtf(x * x + y * y));
}

float	lerp_dist(t_vecf3 a, t_vecf3 b, float t)
{
	float	x;
	float	y;

	x = wall.x - pl->x;
	y = wall.y - pl->y;
	return (sqrtf(x * x + y * y));
}

int		ray_cast(t_engine *engine, t_player *pl, t_line *line, t_map *map)
{
	float	err;
	float	drawing[2];
	int		col;
	int		end;

	float	ratio;
	float	angle;
	float 	epsilon;
	float	diststart;
	float	distend;
	int		xstart;
	int 	xend;


	0	  -		1024;
	-26.562254 - 33.437748;

	if (line->p1 == pl->cam->amin)
		xstart = 0;
	else if (line->p1 == pl->cam->amax)
		xstart = e->xplan;
	else
		xstart = cal;
	if (line->p2 == pl->cam->amin)
		xend = 0;
	else if (line->p2 == pl->cam->amax)
		xend = e->xplan;
	else
		xend = cal;

	diststart = dist2point(pl, line->p1);
	distend = dist2point(pl, line->p2);

	angle = line->angle1;
	epsilon = line->angle1 / line->angle2;

	while (xstart < xend)
	{

		dist2wall = lerp_dist(line->p1, line->p2, angle);
		err = ((float)x * c->fov / (float)(e->xplan)) - pl->cam->half_fov;
		dist2wall *= cosf(err);
		ratio = line->height / (float)player->height;

		drawing[0] =  e->half_yplan - (((float)(e->yplan) / dist2wall) / ratio);
		drawing[1] = (float)(e->yplan) - drawing[0];
		col = x;
		end = (drawing[1] > e->yplan) ? e->yplan : drawing[1];

		draw_wall(e, r, i, drawing);

		angle += epsilon;
	}
	return (SUCCESS);
}
