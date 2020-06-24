#include "../include/bsp.h"

t_player	    init_player(void)
{
	t_player	p;

    p.height = 30;
	p.x = 80.;
	p.y = 80.;
	p.eyes_dirx = 0.06f;
    p.eyes_diry = 0.0f;
    p.eyes_height = 1024 / 2;
	return (p);
}
/*
void		init_global(t_glob *global, t_env *e)
{
	t_cam2d		c;
	t_player	p;
	t_map		mp;
	t_obj_dyn	queen;
	t_obj		gun;

	c = init_cam2d();
	p = init_player();
	mp = init_map();
	queen = init_dynamic(e);
	gun = init_none_dynamic(e);

	global->map = mp;
	global->cam = c;
	global->player = p;
	global->queen = queen;
	global->gun = gun;
}

t_u32		*base_pal(void)
{
	t_u32	*pal;
	int		i;
	float	t;

	if (!(pal = malloc(sizeof(int) * Y_SCREEN)))
		return (0);
	t = 0;
	i = -1;
	while (++i < Y_SCREEN)
	{
		if (i >= Y_MDDL)
			t = i / (float)Y_SCREEN;
		if (i < Y_MDDL)
			pal[i] = 0x383838;
		else
			pal[i] = lerp_non_init_color(0x000000, 0x606D5D, t);
	}
	return (pal);
}
*/
void		init_engine(t_engine *e)
{
	e->mlx_ptr = mlx_init();
	e->win_ptr = mlx_new_window(e->mlx_ptr, WIDTH, HEIGHT, "BSP-DOOM test");
	if (e->mlx_ptr || e->win_ptr == NULL)
		doom_error(e, 0 ^ (1 << 16), "mlx || window fail");
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

	/*
	if ((e->pal = base_pal()) == 0)
		wolf3d_error(e, 3, "e->pal init.c line 79");
	e->map = &(e->global.map);
	e->player = &(e->global.player);
	init_texture(e);
	init_global(&e->global, e);
	*/
}
