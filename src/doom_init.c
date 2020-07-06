#include "../include/bsp.h"
/*
static float 	*update_tabdist()
{}
*/
t_player	    init_player(void)
{
	t_player	p;

    p.height = 30;
	p.x = 80.;
	p.y = 80.;
	p.eyes_dirx = 0.06f;
    p.eyes_diry = 0.0f;
    p.eyes_height = HEIGHT / 2;
	return (p);
}

void		init_global(t_global *global, t_engine *e, t_lst_line *polygons)
{
	t_player	pl;
	t_map		map;

	pl = init_player();
    pl.cam = init_cam2d(pl.x, pl.y, pl.eyes_dirx, (float)e->xplan);
    map = init_map(e, polygons, 1);
	global->player = pl;
	global->map = map;
}

void		init_engine(t_engine *e, t_lst_line *polygons)
{
	e->mlx_ptr = mlx_init();
	e->win_ptr = mlx_new_window(e->mlx_ptr, WIDTH, HEIGHT, "BSP-DOOM test");
	if (e->mlx_ptr == NULL)
		doom_error(e, 0 ^ (1 << 16), "mlx fail");
	if (e->win_ptr == NULL)
		doom_error(e, 0 ^ (1 << 16), "window fail");
	e->xplan = WIDTH;
	e->yplan = HEIGHT;
	e->half_xplan = e->xplan / 2;
	e->half_yplan = e->yplan / 2;

	if (!(e->srcs[0] = init_image(e->mlx_ptr, e->xplan, e->yplan)))
		doom_error(e, 0 ^ (1 << 16), "srcs[0] fail");
	if (!(e->srcs[1] = init_image(e->mlx_ptr, e->xplan, e->yplan)))
		doom_error(e, 0 ^ (1 << 16), "srcs[1] fail");
	e->img = e->srcs[0];
	e->nsrc = 0;
	//e->dist = update_tabdist(e->yplan);

	e->map = &(e->global.map);
	e->player = &(e->global.player);
	init_global(&e->global, e, polygons);

	e->key_a = 0;
	e->key_d = 0;
    e->key_w = 0;
	e->key_s = 0;
}
