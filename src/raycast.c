#include "../include/bsp.h"

static void	info_col(t_engine *e, t_cam2d c, float dist, int x, int nbline)
{
	float       err;
	float 		xscreen;
	float		yscreen;
	int			start_wall;
	int			end_wall;
	int			start;
	int			end;

	xscreen = (float)e->xplan;
	yscreen = (float)e->yplan;
	err = ((float)x * c.fov / xscreen) - c.half_fov;
	dist *= cosf(err);
	start_wall = e->half_yplan - ((yscreen / dist) * 2);
	end_wall = e->yplan - start_wall;
	start = (start_wall < 0) ? 0 : start_wall;
	end = (end_wall > e->xplan) ? e->xplan : end_wall;
	draw_col(e, x, start, end, dist, nbline);
	//printf("dist %f / start %d / end %d\n", dist, start, end);
}

void	raycast(t_engine *e, t_player *pl, t_lst_line *lines)
{
	int 	i;
    int 	x;
    float 	angle;
    t_line 	*line_p;
	float 	*depth;

	x = -1;
	(void)lines;
	ft_bzero(e->img->data, e->xplan * e->yplan * (e->img->bpp / 8));
	depth = (float *)malloc(sizeof(float) * e->xplan);
	ft_bzero(depth, e->xplan * sizeof(float));
	while (++x < e->xplan)
	{
		angle = pl->eyes_dirx + pl->cam.half_fov
			- (float)(x) / (float)(e->xplan) * pl->cam.fov;
        i = -1;
		if (x == 0 || x == 799)
			printf("X == %d angle == %f\n", x, rad2deg(angle));
        while (++i < lines->count)
        {
            line_p = &lines->lst[i];
			//printf("line %d\nangle1 = %f\nangle2 = %f\n", line_p->linedef,
			//	rad2deg(line_p->angle1), rad2deg(line_p->angle2));
			if (angle >= line_p->angle1 && angle <= line_p->angle2)
            {
				//printf("ok\n");
				execute_linear_equation(&lines->leq[i], pl->x, pl->y, angle);
				if (depth[x] == 0 || depth[x] > lines->leq[i].dist)
				{
					depth[x] = lines->leq[i].dist;
					info_col(e, pl->cam, lines->leq[i].dist, x, line_p->linedef);
				}
            }
        }
	}
	free(depth);
	//close_engine(e);
}
