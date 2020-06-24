#include "../include/bsp.h"

void		close_map(t_map *map)
{
    if (map->bsp != NULL)
        close_bsp(map->bsp);
	ft_bzero(map, sizeof(t_map));
}

void		close_engine(t_engine *e, t_map *map)
{
    printf("a\n");
	close_map(map);
    printf("b\n");
    close_image(e->srcs[0], e->mlx_ptr, e->xplan, e->yplan);
	close_image(e->srcs[1], e->mlx_ptr, e->xplan, e->yplan);
    printf("c\n");
    if (e->mlx_ptr != NULL && e->win_ptr != NULL)
        mlx_destroy_window(e->mlx_ptr, e->win_ptr);
    printf("d\n");
    ft_bzero(e, sizeof(t_engine));
    /*
    close_map(&(e->map));
	close_tx(&(e->wall[0]));
	close_tx(&(e->wall[1]));
	close_tx(&(e->wall[2]));
	close_tx(&(e->wall[3]));
	free_secure(e->pal);
	exit(0);
    */
}
