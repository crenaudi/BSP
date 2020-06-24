#include "../include/bsp.h"

int main(void)
{
    t_lst_line  polygons;
    t_player    player;
    t_map       map;
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

    printf("%d\n", polygons.count);

    ft_bzero(&engine, sizeof(t_engine));
    init_engine(&engine);
    player = init_player();
    player.cam = init_cam2d(player.x, player.y, player.eyes_dirx);
    map = init_map(&engine, &polygons, 1);
    bsp_renderer(&player, map.bsp);
    close_engine(&engine, &map);
    printf("\nAU REVOIR !\n");
    return (0);
}
