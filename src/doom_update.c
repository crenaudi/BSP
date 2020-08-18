#include "../include/bsp.h"

float update_hfov(t_engine *e)
{
    return (1.0f * 0.73f * e->yplan / e->xplan);
}

void update_plan(t_engine *e, int h, int w)
{
    if (e->srcs[0])
        close_image(e->srcs[0], e->mlx_ptr, e->xplan, e->yplan);
    if (e->srcs[1])
	   close_image(e->srcs[1], e->mlx_ptr, e->xplan, e->yplan);
    e->xplan = w;
	e->yplan = h;
	e->half_xplan = e->xplan / 2;
	e->half_yplan = e->yplan / 2;
    update_srcs(e);
}

void update_srcs(t_engine *e)
{
    if (!(e->srcs[0] = init_image(e->mlx_ptr, e->xplan, e->yplan)))
		doom_error(e, 0 ^ (1 << 16), "srcs[0] fail");
	if (!(e->srcs[1] = init_image(e->mlx_ptr, e->xplan, e->yplan)))
		doom_error(e, 0 ^ (1 << 16), "srcs[1] fail");
}
