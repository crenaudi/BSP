#include "../include/bsp.h"

int		evaluate_pointonview(t_cam2d c, float x, float y)
{
	float 	angle;
	float	dist;
	t_vecf2	fvec;

	fvec.x = x - c.dvl.p.x;
	fvec.y = y - c.dvl.p.y;
	dist = sqrtf(fvec.x * fvec.x + fvec.y * fvec.y);
    angle = atan2f(c.dvl.dy, c.dvl.dx) - atan2f(fvec.y, fvec.x);
    if (angle < -3.14159f)
        angle += 2 * 3.14159f;
    if (angle > 3.14159f)
        angle -= 2 * 3.14159f;
	if (fabs(angle) < c.half_fov && dist >= 0.5f && dist < c.depth)
		return (SUCCESS);
    else
        return (ERROR);
}

int		seg_onview(t_cam2d c, t_line line)
{
	t_vecf2 far;
	t_vecf2 x[2];
	t_vecf2 y[2];

	if (evaluate_pointonview(c, line.p1.x, line.p1.y) == SUCCESS)
        return (SUCCESS);
    if (evaluate_pointonview(c, line.p2.x, line.p2.y) == SUCCESS)
        return (SUCCESS);
	x[0] = c.dvl.p;
	x[1].x = c.dvl.p.x + c.dvl.dx * c.depth;
	x[1].y = c.dvl.p.y + c.dvl.dy * c.depth;
	y[0] = line.p1;
	y[1] = line.p2;
	if (intersect_line(x, y, 0) == 1)
		return (SUCCESS);
	return (ERROR);
}

void walk_tree(t_bspnode *node, t_cam2d c, t_lst_line *p_lines)
{
    int side;

    side = pointonside(c.dvl.p, &node->divline);
    if (p_lines->count < 255)
        if (node->side[side] != NULL)
            walk_tree(node->side[side], c, p_lines);
    if (seg_onview(c, node->line) == SUCCESS)
    {
        printf("--> line %d is onview\n", node->line.linedef);
		cpy_line(&p_lines->lst[p_lines->count], &node->line);
        p_lines->count++;
    }
    if (p_lines->count < 255)
        if (node->side[side ^ 1] != NULL)
            walk_tree(node->side[side ^ 1], c, p_lines);
}

void    bsp_renderer(t_player *pl, t_bspnode *node)
{
    t_bspnode   *tmp;
	t_lst_line 	p_lines;
	int			i;

	tmp = node;
    pl->cam.dvl.p = (t_vecf2){pl->coord_x, pl->coord_x};
    pl->cam.dvl.dx = sinf(pl->eyes_dir);
    pl->cam.dvl.dy = cosf(pl->eyes_dir);
	bzero(&p_lines, sizeof(t_lst_line));
    walk_tree(tmp, pl->cam, &p_lines);
	i = -1;
	printf("PRINTABLE LINES\n");
	while (++i < p_lines.count)
		printf("line %d : %f,%f - %f,%f\n", p_lines.lst[i].linedef, p_lines.lst[i].p1.x,
			p_lines.lst[i].p1.y, p_lines.lst[i].p2.x, p_lines.lst[i].p2.y);
}

/*
void WalkTree(t_bspnode *node)
{
   t_bspnode *nodestack[256];
   t_bspnode **ptr_nodestack;
   int side;

   // Make sure the tree isn’t empty
   if (node != NULL)
   {
      nodestack[0] = NULL;
      ptr_nodeStack = nodestack + 1;
      for (;;)
      {
         while (node[side] != NULL)
         {
            side = pointonside((t_vecf2){pl->coord_x, pl->coord_y}, &node->divline);
            *ptr_nodeStack++ = node;
            node = node[side];
         }
         //node est donc le point le plus proche devant
         for (;;)
         {
            Visit(node);
            if (node[side ^ 1] != NULL)
            {
               node = node[side ^ 1];
               break;
            }
            if ((node = * —nodeStack) == NULL)
               return;
         }
      }
   }
}*/
