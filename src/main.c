#include "../include/bsp.h"

static t_polygon    info(t_vecf3 p1, t_vecf3 p2, int *n, int sided)
{
    t_polygon   p;

    *n += 1;
    p.n = *n;
    p.p1 = p1;
    p.p2 = p2;
    p.mod = 0;
    p.flags = sided;
    p.sector = 0;
    return (p);
}

static t_cam2d		init_cam2d(void)
{
	t_cam2d		c;

	bzero(&c, sizeof(t_cam2d));
	c.fov = 3.14159f / 3.0f;
	c.half_fov = c.fov / 2.0f;
    c.clipangle = 2 * c.fov;
    c.depth = 160.f;
    c.dvl.p.x = 0.f;
    c.dvl.p.y = 0.f;
    c.dvl.dx = 0.f;
    c.dvl.dy = 0.f;
	return (c);
}

static t_player	    init_player(void)
{
	t_player	p;

    p.height = 30;
	p.coord_x = 80.;
	p.coord_y = 80.;
	p.eyes_dirx = 0.06f;
    p.eyes_diry = 0.0f;
    p.eyes_height = 1024 / 2;
	return (p);
}

int main(void)
{
    t_polygon   p[256];
    int         n;
    t_player    player;

    n = 0;
    p[0] = info((t_vecf3){20,50,60}, (t_vecf3){70,20,60}, &n, 0);
    p[1] = info((t_vecf3){70,20,60}, (t_vecf3){180,20,60}, &n, 0);
    p[2] = info((t_vecf3){180,20,60}, (t_vecf3){220,60,60}, &n, 0);
    p[3] = info((t_vecf3){220,60,60}, (t_vecf3){270,60,60}, &n, 0);
    p[4] = info((t_vecf3){270,60,60}, (t_vecf3){270,90,60}, &n, 0);
    p[5] = info((t_vecf3){270,90,60}, (t_vecf3){240,90,60}, &n, 0);
    p[6] = info((t_vecf3){240,90,60}, (t_vecf3){160,180,60}, &n, 0);
    p[7] = info((t_vecf3){160,180,60}, (t_vecf3){20,140,60}, &n, 0);
    p[8] = info((t_vecf3){20,140,60}, (t_vecf3){20,50,60}, &n, 0);
    p[9] = info((t_vecf3){90,120,60}, (t_vecf3){50,70,60}, &n, TWOSIDED);
    p[10] = info((t_vecf3){50,70,60}, (t_vecf3){70,50,60}, &n, TWOSIDED);
    p[11] = info((t_vecf3){70,50,60}, (t_vecf3){120,110,60}, &n, TWOSIDED);
    p[12] = info((t_vecf3){120,110,60}, (t_vecf3){170,50,60}, &n, TWOSIDED);
    p[13] = info((t_vecf3){170,50,60}, (t_vecf3){140,20,60}, &n, TWOSIDED);
    printf("%d\n", n);
    player = init_player();
    player.cam = init_cam2d();
    make_bsp(p, n, &player);
    //bsp_renderer(&player, node);
    return (0);
}
