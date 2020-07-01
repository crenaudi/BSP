#include "../include/bsp.h"
/*
static float	distforay(t_player *pl, t_line *line, float angle)
{
	float       frac;
	t_vecf2     new;
	t_vecf2     dist;
	t_divline   seg;
	t_divline   player;

	make_divline(&seg, line->p1, line->p2);
	new.x = pl->x + sinf(angle) * pl->cam.depth;
    new.y = pl->y + cosf(angle) * pl->cam.depth;
	player.p = pl->cam.dvl_lr.p;
	player.dx = new.x - pl->x;
	player.dy = new.y - pl->y;
	frac = intersect_vector(&seg, &player);
	new.x = seg.p.x + float_round(seg.dx * frac);
	new.y = seg.p.y + float_round(seg.dy * frac);
	dist.x = new.x - pl->x;
	dist.y = new.y - pl->y;
	return (sqrtf(dist.x * dist.x + dist.y * dist.y));
}
*/

static float distmin(t_vecf3 p1, float plx, float ply)
{
	float x;
	float y;

	x = p1.x - plx;
	y = p1.y - ply;
	return (sqrtf(x * x + y * y));
}

static float distmax(t_vecf3 p2, float plx, float ply)
{
	float x;
	float y;

	x = p2.x - plx;
	y = p2.y - ply;
	return (sqrtf(x * x + y * y));
}

static void	info_col(t_engine *e, t_cam2d c, float dist, int x)
{
	float       err;
	float 		xscreen;
	float		yscreen;
	int			start_wall;
	int			end_wall;
	int			start;
	int			end;

	printf("dist = %f\n", dist);
	xscreen = (float)e->xplan;
	yscreen = (float)e->yplan;
	err = ((float)x * c.fov / xscreen) - c.half_fov;
	dist *= cosf(err);
	start_wall = e->half_yplan - (yscreen / dist);
	end_wall = e->yplan - start_wall;
	start = (start_wall < 0) ? 0 : start_wall;
	end = (end_wall > e->xplan) ? e->xplan : end_wall;
	printf("start_wall %d end_wall %d || start %d end %d\n", start_wall, end_wall, start, end);
	draw_col(e, x, start, end, dist);
	printf("\n");
}

void	raycast(t_engine *e, t_player *pl, t_lst_line *lines)
{
	int 	i;
    int 	x;
    float 	angle;
    t_line 	*line_p;

	x = -1;
	ft_bzero(e->img->data, e->xplan * e->yplan * (e->img->bpp / 8));
	while (++x < e->xplan)
	{
		angle = (float)(pl->eyes_dirx - pl->cam.half_fov)
			+ (float)(x) / (float)(e->xplan) * pl->cam.fov;
        i = -1;
		printf("X == %d\n", x);
        while (++i < lines->count)
        {
            line_p = &lines->lst[i];
            if (angle >= line_p->angle1 && angle <= line_p->angle2)
            {
				if (x == 0)
					lines->leq[i].dist = distmin(line_p->p1, pl->x, pl->y);
				else if (x == e->xplan)
					lines->leq[i].dist = distmax(line_p->p2, pl->x, pl->y);
				else
					execute_linear_equation(&lines->leq[i], pl->x, pl->y, angle);
				info_col(e, pl->cam, lines->leq[i].dist, x);
            }
			if (x == 1)
				close_engine(e);
			if (line_p->twoside == 0)
				break;
        }
	}
}
