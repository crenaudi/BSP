#include "../include/bsp.h"

int		seg_onview(t_cam2d c, t_line *line, t_vecf2 depth)
{
	float 	plx;
	float 	ply;
	t_vecf2 x[2];
	t_vecf2 y[2];

	plx = c.dvl_lr.p.x;
	ply = c.dvl_lr.p.y;
	if (evaluate_pointonview(c, c.dvl_lr, line->p1.x, line->p1.y) == SUCCESS)
		return (SUCCESS);
	if (evaluate_pointonview(c, c.dvl_lr, line->p2.x, line->p2.y) == SUCCESS)
		return (SUCCESS);

	x[0].x = plx;
	x[0].y = ply;
	x[1].x = depth.x;
	x[1].y = depth.y;
	y[0].x = line->p1.x;
	y[0].y = line->p1.y;
	y[1].x = line->p2.x;
	y[1].y = line->p2.y;
	if (evaluate_intersect_line(x, y, 0) == 1)
		return (SUCCESS);
	return (ERROR);
}

void walk_tree(t_bspnode *node, t_cam2d c, t_lstl *p_lines, t_vecf2 depth)
{
    int side;

    side = pointonside(c.dvl_lr.p, &node->divline);
    if (p_lines->count < 255 && side != -1)
        if (node->side[side] != NULL)
            walk_tree(node->side[side], c, p_lines, depth);
    if (seg_onview(c, &node->line, depth) == SUCCESS)
    {
		cpyl(&p_lines->lst[p_lines->count], &node->line);
        p_lines->count++;
    }
    if (p_lines->count < 255 && side != -1)
        if (node->side[side ^ 1] != NULL && node->line.twoside == 1)
            walk_tree(node->side[side ^ 1], c, p_lines, depth);
}

void    bsp_renderer(t_engine *e, t_player *pl, t_bspnode *node)
{
	t_lstl 	p_lines;
	t_vecf2 	depth;

	init_lstline(&p_lines);
	depth.x = pl->cam.dvl_lr.p.x + pl->cam.dvl_lr.dx * pl->cam.depth;
	depth.y = pl->cam.dvl_lr.p.y + pl->cam.dvl_lr.dy * pl->cam.depth;
	walk_tree(node, pl->cam, &p_lines, depth);
	raycast(e, &p_lines);
}
