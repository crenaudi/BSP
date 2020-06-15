//#include "../include/bsp.h"
#include "../include/bsp-v1.h"

static t_polygon    info(t_vecf2 p1, t_vecf2 p2, int *n, int sided)
{
    t_polygon   p;

    *n += 1;
    p.n = *n;
    p.p1 = p1;
    p.p2 = p2;
    p.high = 0;
    p.mod = 0;
    p.flags = sided;
    p.sector = 0;
    return (p);
}

static t_cam2d		init_cam2d(void)
{
	t_cam2d		c;

	bzero(&c, sizeof(t_cam2d));
	c.fov = 3.1415927 / 3;
	c.half_fov = c.fov / 2.0f;
	c.dir = 0;
	return (c);
}

static t_player	    init_player(void)
{
	t_player	p;

	p.coord_x = 8.;
	p.coord_y = 8.;
	p.eyes_dir = 0.06f;
	return (p);
}

int main(void)
{
    t_polygon   p[256];
    int         n;
    t_player    player;

    n = 0;
    p[0] = info((t_vecf2){2,5}, (t_vecf2){7,2}, &n, 0);
    p[1] = info((t_vecf2){7,2}, (t_vecf2){18,2}, &n, 0);
    p[2] = info((t_vecf2){18,2}, (t_vecf2){22,6}, &n, 0);
    p[3] = info((t_vecf2){22,6}, (t_vecf2){27,6}, &n, 0);
    p[4] = info((t_vecf2){27,6}, (t_vecf2){27,9}, &n, 0);
    p[5] = info((t_vecf2){27,9}, (t_vecf2){24,9}, &n, 0);
    p[6] = info((t_vecf2){24,9}, (t_vecf2){16,18}, &n, 0);
    p[7] = info((t_vecf2){16,18}, (t_vecf2){2,14}, &n, 0);
    p[8] = info((t_vecf2){2,14}, (t_vecf2){2,5}, &n, 0);
    p[9] = info((t_vecf2){9,12}, (t_vecf2){5,7}, &n, TWOSIDED);
    p[10] = info((t_vecf2){5,7}, (t_vecf2){7,5}, &n, TWOSIDED);
    p[11] = info((t_vecf2){7,5}, (t_vecf2){12,11}, &n, TWOSIDED);
    p[12] = info((t_vecf2){12,11}, (t_vecf2){17,5}, &n, TWOSIDED);
    p[13] = info((t_vecf2){17,5}, (t_vecf2){14,2}, &n, TWOSIDED);
    printf("%d\n", n);
    player = init_player();
    player.cam = init_cam2d();
    make_bsp(p, n, &player);
    //bsp_renderer(&player, node);
    return (0);
}
