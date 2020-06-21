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

int				dda_ray(t_ray *r, t_player *p, t_map *map)
{
	r->ray.x = sinf(r->ray_angle);
	r->ray.y = cosf(r->ray_angle);
	r->ray_dist = 0;
	while (r->hit != 1)
	{
		if (r->ray_dist.x < r->ray_dist.y)
			r->ray_dist.x += EPSILON;
		else
			r->ray_dist.y += EPSILON;
		r->map_x = (int)(p->coord_x + r->ray.x * r->ray_dist.x);
		r->map_y = (int)(p->coord_y + r->ray.y * r->ray_dist.y);
		if (r->map_y > map->size_y || r->map_x > map->size_x)
			return (ERROR);
		if (map->data[r->map_y][r->map_x] != 0)
		{
			r->hit = map->data[r->map_y][r->map_x];
			dda_info_txtur(r, p);
		}
	}
	return (SUCCESS);
}

int				ray_cast(t_env *e, t_cam2d *c)
{
	float	err;
	float	drawing[2];
	int		x;
	int		i[3];
	t_ray	r;

	x = -1;
	while (++x < X_SCREEN)
	{
		r.ray_angle = (float)(e->player->eyes_dir - c->half_fov)
			+ (float)(x) / (float)(X_SCREEN) * c->fov;
		r.hit = 0;
		if (dda_ray(&r, e->player, e->map) == SUCCESS)
		{
			err = ((float)x * c->fov / (float)(X_SCREEN)) - c->half_fov;
			r.ray_dist *= cosf(err);
			drawing[0] = pl->eyes_height - (((float)(Y_SCREEN) / ((r.ray_dist.x
				< r.ray_dist.y) ? r.ray_dist.x : r.ray_dist.y)) / 1.5f);
			drawing[1] = (float)(Y_SCREEN) - drawing[0];
			i[0] = x;
			i[2] = (drawing[1] > Y_SCREEN) ? Y_SCREEN : drawing[1];
			draw_wall(e, r, i, drawing);
		}
	}
	return (SUCCESS);
}
