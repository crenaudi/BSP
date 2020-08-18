#include "../include/bsp.h"

static float min(float a, float b)
{
	return ((a < b)? a : b);
}

static float max(float a, float b)
{
	return ((a > b)? a : b);
}

static void 	vline(t_engine *e, int x, int y1, int y2, int top, int middle, int bottom)
{
	int y;

    y1 = min(max(y1, 0), e->yplan - 1);
    y2 = min(max(y2, 0), e->yplan - 1);
	printf("%d %d\n", y1, y2);
    if(y2 == y1)
        e->img->data[y1 * e->xplan + x] = middle;
    else if(y2 > y1)
    {
        e->img->data[y1 * e->xplan + x] = top;
		y = y1;
        while (++y < y2)
			e->img->data[y * e->xplan + x] = middle;
        e->img->data[y2 * e->xplan + x] = bottom;
    }
}

static void 	render_wall(t_engine *e, t_vxinfo *vx, short *ytop, short *ybottom)
{
	int			x;
	int			beginx;
	int 		endx;
	int			ya;
	int			yb;
	int			cya;
	int			cyb;

	beginx = max(vx->x1, 0);
	endx = min(vx->x2, e->xplan - 1);
	x = beginx - 1;
	//printf("%d %d\n", x, endx);
	while (++x <= endx)
	{
		ya = (x - vx->x1) * (vx->y2a - vx->y1a) / (vx->x2 - vx->x1) + vx->y1a;
		yb = (x - vx->x1) * (vx->y2b - vx->y1b) / (vx->x2 - vx->x1) + vx->y1b;
		cya = min(max(ya, ytop[x]), ybottom[x]);//top
		cyb = min(max(yb, ytop[x]), ybottom[x]);//bottom
		vline(e, x, ytop[x], cya - 1, 0x111111, 0x222222, 0x111111);
		vline(e, x, cyb + 1, ybottom[x], 0x0000FF, 0x0000AA, 0x0000FF);
	}
}

static int 	perspective_transform(t_engine *e, t_vxinfo *vx, float floor, float ceil)
{
	float	xscale1;
	float	xscale2;
	float	yscale1;
	float	yscale2;

	xscale1 = e->hfov / vx->tz1;
	xscale2 = e->hfov / vx->tz2;
	yscale1 = e->vfov / vx->tz1;
	yscale2 = e->vfov / vx->tz2;
	vx->x1 = e->half_xplan - (int)(vx->tx1 * xscale1);
	vx->x2 = e->half_xplan - (int)(vx->tx2 * xscale2);
	if (vx->x1 >= vx->x2 || vx->x2 < 0 || vx->x1 > e->xplan - 1)
	{
		vx->yceil = ceil - e->player->z;
		vx->yfloor = floor - e->player->z;
		vx->y1a = e->half_yplan - (int)(vx->yceil * yscale1);
		vx->y2a = e->half_yplan - (int)(vx->yceil * yscale2);
		vx->y1b = e->half_yplan - (int)(vx->yfloor * yscale1);
		vx->y2b = e->half_yplan - (int)(vx->yfloor * yscale2);
		return (SUCCESS);
	}
	return (ERROR);
}

static int init_top_bottom(t_engine *e, short *top, short *bottom)
{
	int	i;

	if (!(top = (short *)malloc(sizeof(short) * e->xplan)))
		return (ERROR);
	if (!(bottom = (short *)malloc(sizeof(short) * e->xplan)))
 		return (ERROR);
	i = -1;
	while (++i < e->xplan)
	{
		top[i] = 0;
		bottom[i] = e->yplan - 1;
	}
	return (SUCCESS);
}

void 	raycast(t_engine *e, t_lstl *lstl)
{
	int			x;
	int 		i;
	//t_sector	sector;
	t_vxinfo	vx;
	short		*top;
	short		*bottom;

	x = -1;
	while (++x < e->xplan)
	{
		top = NULL;
		bottom = NULL;
		if (init_top_bottom(e, top, bottom) == SUCCESS)
		{
			i = -1;
			while (++i < lstl->count)
			{
				//printf("lstl->count %d i %d", lstl->count, i);
				if (precompute_vertex(&vx, &lstl->lst[i], e->player) == SUCCESS)
				{
					if (perspective_transform(e, &vx, 0, 6) == SUCCESS)
						render_wall(e, &vx, top, bottom);
				}
			}
			free(top);
			free(bottom);
		}
	}
}
