#include "../include/bsp.h"


void cal_b(t_vecf2 p, t_divline *d)
{
	float b;

	//y = (d->dy / d->dx) * x + b
	//d->p.y = (d->dy / d->dx) * d->p.x + b
	b = d->p.y - ((d->dy / d->dx) * d->p.x);
}

void cal_b(t_vecf2 p, t_divline *d)
{
	float a;
	float b;
	float plan;

	a = d->dy / d->dx;
	plan = d->p.y - (a * d->p.x);
	b = p.y - (p.x * tan(angle));
/*
	y' = x' * tan(angle) + b
	a * x' + plan = x' * tan(angle) + b;
	x' * d->dy + (plan * d->dx) = (x * d->dx) * tan(angle) + (p.y * d->dx) - (p.x * d->dx) * tan(angle);
	x' * d->dy - (x' * d->dx) * tan(angle) = ((plan * d->dx) - (p.y * d->dx)) - (p.x * d->dx) * tan(angle);
*/
	plan *= d->dx;
	px = p.x * d->dx;
	py = p.y * d->dx;
	x' - (x' * d->dx) * tan(angle) = (plan - py) - px * tan(angle);
	plan = py - plan;
	x' =  (plan - px) * tan(angle) / (dy - dx) * tan(angle);
/*
	y' = a * x' + b;
	y' = (dy / dx) * (x') +  p.y - (p.x * tan(angle));
	y' = (dy / dx) * (plan - px * tan(angle) / (dy - dx) * tan(angle)) +  p.y - (p.x * tan(angle));
	y' = (plan / dx) - (px / dx) * tan(angle) +  (b * (dy / dy)) - (b * (dx / dy)) * tan(angle);
		___________________________________   ________________________________________________
		((dy / dy) - (dx / dy)) * tan(angle)   (1 * (dy / dy) - 1 * (dx / dy)) * tan(angle)
*/
	divxy = d->dx / d->dy;
	divyy = d->dy / d->dy;
	plan = (plan / d->dx) + b * divyy;
	b *= divxy;
	y' = (plan - ((px / d->dx) + b)) * tan(angle) / (divyy - divxy) * tan(angle);
}

/*
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
*/

static float	distforay(t_player *pl, t_line *line, float angle)
{
	float       frac;
	t_vecf2     new;
	t_vecf2     dist;
	t_divline   seg;
	t_divline   player;

	make_divline(&seg, line->p1, line->p2);
	new.x = pl->x + sinf(angle) * pl->cam.depth;
    new.y = pl->y + cosf(angle) * pl->cam.depth;
	player.p = pl->cam.dvl_lr.p;
	player.dx = new.x - pl->x;
	player.dy = new.y - pl->y;
	frac = intersect_vector(&seg, &player);
	new.x = seg.p.x + float_round(seg.dx * frac);
	new.y = seg.p.y + float_round(seg.dy * frac);
	dist.x = new.x - pl->x;
	dist.y = new.y - pl->y;
	return (sqrtf(dist.x * dist.x + dist.y * dist.y));
}

static void	info_col(t_engine *e, t_cam2d c, float dist, int x)
{
	float       err;
	float 		xscreen;
	float		yscreen;
	int			start_wall;
	int			end_wall;
	int			start;
	int			end;

	xscreen = (float)e->xplan;
	yscreen = (float)e->yplan;
	err = ((float)x * c.fov / xscreen) - c.half_fov;
	dist *= cosf(err);
	start_wall = e->half_yplan - (yscreen / dist);
	end_wall = e->yplan - start_wall;
	start = (start_wall < 0) ? 0 : start_wall;
	end = (end_wall > e->xplan) ? e->xplan : end_wall;
	//printf("start_wall %d end_wall %d || start %d end %d\n", start_wall, end_wall, start, end);
	draw_col(e, x, start, end, dist);
}

void	raycast(t_engine *e, t_player *pl, t_lst_line *lines, t_info_line info[255])
{
	int 	i;
    int 	x;
    float 	angle;
    t_line 	*line_p;
	float 	dist;

	x = -1;
	(void)info;
	ft_bzero(e->img->data, e->xplan * e->yplan * (e->img->bpp / 8));
	while (++x < e->xplan)
	{
		angle = (float)(pl->eyes_dirx - pl->cam.half_fov)
			+ (float)(x) / (float)(e->xplan) * pl->cam.fov;
        i = -1;
        while (++i < lines->count)
        {
            line_p = &lines->lst[i];
            if (angle >= line_p->angle1 && angle <= line_p->angle2)
            {
				dist = distforay(pl, line_p, angle);
                //printf("col %d, l. %d, dist : %f\n", x, line_p->linedef, dist);
				info_col(e, pl->cam, dist, x);
            }
			if (line_p->twoside == 0)
				break;
        }
	}
}
