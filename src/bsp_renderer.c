#include "../include/bsp.h"

struct					s_cam2d
{
	float				fov;
	float				half_fov;
	float				speed_move;
	float				speed_angle;
	t_vecf2				dir;
};

struct			s_player
{
    t_cam2d		camera;
	float		coord_x;
	float		coord_y;
	float		eyes_dir;
	int			pos_x;
	int			pos_y;
	int			wp;
	int			pv;
};

void   render_lstlines(t_lst_line *plines, t_bspnode *node, t_player *pl)
{
    int side;

    if (plines->count >= 255 || node->side == 1)
    {
        cpy_line(&plines[plines->count], &node->line);
        return ;
    }
    if (/*node == side 1 && plines->count < 256*/ && node->side[0] == visible && none already in list)
    {
        render_lstlines(pl, node->side[0], pl);
        cpy_line(&plines[plines->count], &node->line);
        plines->count++;
    }
    if (/*node == side 1 && plines->count < 256*/ node->side[1] == visible && none already in list)
    {
        cpy_line(&plines[plines->count], &node->line);
        plines->count++;
        render_lstlines(pl, node->side[1], pl);
    }
    return ;
}

t_bspnode   *first_visible_node(t_player *pl, t_map *mp)
{
    if (node == visible)
        return (node);
    else
        (point on side == font) ?
        sort_first_visible_node(node->side[0], pl) :
        sort_first_visible_node(node->side[1], pl);
}

void    bsp_renderer(t_player *pl, t_map *mp)
{
    t_lst_line  plines;
    t_bspnode   *tmp;

	tmp = map->bsp;
    tmp = first_visible_node(tmp, pl);
    plines.count = 0;
    make_printable_list(&plines, tmp, pl);
}
