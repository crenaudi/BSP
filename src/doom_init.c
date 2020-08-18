#include "../include/bsp.h"

t_player	    init_player(void)
{
	t_player	p;

    p.height = 30;
	p.x = 80.;
	p.y = 80.;
	p.eyes_dirx = deg2rad(45);
    p.eyes_diry = 0.0f;
    p.eyes_height = HEIGHT / 2;
	return (p);
}

void		init_global(t_global *global, t_engine *e, t_lstl *polygons)
{
	t_player	pl;
	t_map		map;

	pl = init_player();
    pl.cam = init_cam2d(pl.x, pl.y, pl.eyes_dirx, (float)e->xplan);
    map = init_map(e, polygons, 1);
	global->player = pl;
	global->map = map;
}

void		init_engine(t_engine *e, t_lstl *polygons)
{
	if ((e->mlx_ptr = mlx_init()) == NULL)
		doom_error(e, 0 ^ (1 << 16), "mlx fail");
	if ((e->win_ptr = mlx_new_window(e->mlx_ptr, WIDTH, HEIGHT,
		"BSP-DOOM test")) == NULL)
		doom_error(e, 0 ^ (1 << 16), "window fail");

	update_plan(e, HEIGHT, WIDTH);
	e->img = e->srcs[0];
	e->nsrc = 0;
	e->map = &(e->global.map);
	e->player = &(e->global.player);
	init_global(&e->global, e, polygons);
	e->hfov = update_hfov(e);//horizontal
	e->vfov = 1.0f * 0.2f;//vertical
	e->key_a = 0;
	e->key_d = 0;
    e->key_w = 0;
	e->key_s = 0;
}
