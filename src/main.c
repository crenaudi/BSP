#include "../include/bsp.h"

int     run(t_engine *e)
{
	t_bspnode *map;

	map = e->map->bsp;
	check_move(e);
    bsp_renderer(e, e->player, map);
    mlx_put_image_to_window(e->mlx_ptr, e->win_ptr, e->img->ptr, 0, 0);
	if (e->nsrc)
		e->img = e->srcs[0];
	else
		e->img = e->srcs[1];
	e->nsrc = !e->nsrc;
    return (SUCCESS);
}

int main(void)
{
    t_lst_line  polygons;
    t_engine    engine;

    init_lstline(&polygons);
    add_polygon2list(&polygons, (t_vecf3){20,50,60}, (t_vecf3){70,20,60}, 0, 1);
    add_polygon2list(&polygons, (t_vecf3){70,20,60}, (t_vecf3){180,20,60}, 0, 1);
    add_polygon2list(&polygons, (t_vecf3){180,20,60}, (t_vecf3){220,60,60}, 0, 1);
    add_polygon2list(&polygons, (t_vecf3){220,60,60}, (t_vecf3){270,60,60}, 0, 1);
    add_polygon2list(&polygons, (t_vecf3){270,60,60}, (t_vecf3){270,90,60}, 0, 1);
    add_polygon2list(&polygons, (t_vecf3){270,90,60}, (t_vecf3){240,90,60}, 0, 1);
    add_polygon2list(&polygons, (t_vecf3){240,90,60}, (t_vecf3){160,180,60}, 0, 1);
    add_polygon2list(&polygons, (t_vecf3){160,180,60}, (t_vecf3){20,140,60}, 0, 1);
    add_polygon2list(&polygons, (t_vecf3){20,140,60}, (t_vecf3){20,50,60}, 0, 1);
    add_polygon2list(&polygons, (t_vecf3){90,120,60}, (t_vecf3){50,70,60}, TWOSIDED, 1);
    add_polygon2list(&polygons, (t_vecf3){50,70,60}, (t_vecf3){70,50,60}, TWOSIDED, 1);
    add_polygon2list(&polygons, (t_vecf3){70,50,60}, (t_vecf3){120,110,60}, TWOSIDED, 1);
    add_polygon2list(&polygons, (t_vecf3){120,110,60}, (t_vecf3){170,50,60}, TWOSIDED, 1);
    add_polygon2list(&polygons, (t_vecf3){170,50,60}, (t_vecf3){140,20,60}, TWOSIDED, 1);

    ft_bzero(&engine, sizeof(t_engine));
    init_engine(&engine, &polygons);
    mlx_loop_hook(engine.mlx_ptr, run, &engine);
	mlx_hook(engine.win_ptr, 2, (1L << 0), key_press, &engine);
	mlx_hook(engine.win_ptr, 3, (1L << 1), key_release, &engine);
    mlx_hook(engine.win_ptr, 17, (1L << 17), close_hook, &engine);
	mlx_loop(engine.mlx_ptr);

    return (0);
}
