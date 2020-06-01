#include "../include/bsp.h"

static t_polygon info(t_vecf2 p1, t_vecf2 p2, int *n, int sided)
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

int main(void)
{
    t_polygon   p[256];
    int         n;

    n = 0;
    p[0] = info((t_vecf2){2,6}, (t_vecf2){2,11}, &n, 0);
    p[1] = info((t_vecf2){2,11}, (t_vecf2){8,13}, &n, 0);
    p[2] = info((t_vecf2){8,13}, (t_vecf2){11,10}, &n, 0);
    p[3] = info((t_vecf2){11,10}, (t_vecf2){9,3}, &n, 0);
    p[4] = info((t_vecf2){9,3}, (t_vecf2){2,6}, &n, 0);
    p[5] = info((t_vecf2){6,6}, (t_vecf2){8,8}, &n, TWOSIDED);
    p[6] = info((t_vecf2){4,10}, (t_vecf2){6,6}, &n, TWOSIDED);
    p[7] = info((t_vecf2){6,9}, (t_vecf2){8,11}, &n, TWOSIDED);
    make_bsp(p, n);
    return (0);
}
