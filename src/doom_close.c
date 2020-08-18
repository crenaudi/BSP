#include "../include/bsp.h"

void	close_map(t_map *map)
{
    if (map->bsp)
        close_bsp(map->bsp);
    if (map->sectors)
        free(map->sectors);
	ft_bzero(map, sizeof(t_map));
}

void    close_engine(t_engine *e)
{
    if (e->map)
	   close_map(e->map);
    if (e->srcs[0])
        close_image(e->srcs[0], e->mlx_ptr, e->xplan, e->yplan);
    if (e->srcs[1])
	   close_image(e->srcs[1], e->mlx_ptr, e->xplan, e->yplan);
    if (e->mlx_ptr != NULL && e->win_ptr != NULL)
        mlx_destroy_window(e->mlx_ptr, e->win_ptr);
    ft_bzero(e, sizeof(t_engine));
    printf("Au revoir !\n");
    exit(0);
}

int     close_hook(t_engine *e)
{
    close_engine(e);
    return (SUCCESS);
}
