#include "../include/bsp.h"

t_cam2d		init_cam2d(t_player *pl)
{
	t_cam2d		c;

	bzero(&c, sizeof(t_cam2d));
	c.fov = 3.14159f / 3.0f;
	c.half_fov = c.fov / 2.0f;
    c.clipangle = 2 * c.fov;
    c.depth = 160.f;
    update_cam2d(&c, pl);
	return (c);
}

void		update_cam2d(t_cam2d *c, t_player *pl)
{
    c->dvl_lr.p = (t_vecf3){pl->x, pl->x, 0};
    c->dvl_lr.dx = sinf(pl->eyes_dirx);
    c->dvl_lr.dy = cosf(pl->eyes_dirx);
    c->depthright.x = pl->x * sinf(pl->eyes_dirx + c->half_fov) * c->depth;
    c->depthright.y = pl->y * cosf(pl->eyes_dirx + c->half_fov) * c->depth;
    c->depthleft.x = pl->x * sinf(pl->eyes_dirx - c->half_fov) * c->depth;
    c->depthleft.y = pl->y * cosf(pl->eyes_dirx - c->half_fov) * c->depth;
    c->dvl_fb.p = (t_vecf3){c->depthright.x, c->depthright.y, 0};
    c->dvl_fb.dx = c->depthleft.x - c->depthright.x;
    c->dvl_fb.dy = c->depthleft.y - c->depthright.y;
}
