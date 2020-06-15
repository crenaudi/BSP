#include "../include/bsp.h"
#include "../include/bsp-v1.h"

t_bspnode *first_visible_node(t_bspnode *node, t_player *pl)
{
	if (node is on view)
		first_visible_node(node->side[(pointonside((t_vecf2){pl->coord_x,
			pl->coord_y}, bsp->divline)], pl);
	else
		return (node);
}
