#include "../include/bsp.h"

static int find_outcode(float angle, t_vecf3 p, t_cam2d c)
{
    int outcode0;
    int outcode1;

    if (angle != 0)
        return (0);
    outcode0 = pointonside(p, &c.dvl_lr);
    outcode1 = pointonside(p, &c.dvl_fb);
    if (outcode1 == 1)
        return ((outcode0 == 1) ? 1 : 2);
    return ((outcode1 == 1) ? 0 : 3);
}

void precompute(t_lst_line *lstlines, t_player *pl)
{
    int         i;
    t_vecf3     right;
    t_vecf3     left;
    t_line      line;
    int         outcode;

    i = -1;
    while (++i < lstlines->count)
    {
        line = lstlines->lst[i];
        printf("\nLINE %d :\n", line.linedef);
        outcode = find_outcode(line.angle1, line.p1, pl->cam);
        if (outcode == 1)
        {
            printf("p1 -> right\n");
        }
        else if (outcode == 2)
        {
            printf("p1 -> left\n");
        }
        else if (outcode == 3)
        {
            printf("p1 -> derriere\n");
        }
        else
            printf("p1 -> inside\n");
            /*
        if (outcode != 0)
        {
            p1 = new_point(outcode, p1, c, right, left);
        }*/
        outcode = find_outcode(line.angle2, line.p2, pl->cam);
        if (outcode == 1)
            printf("p2 -> right\n");
        else if (outcode == 2)
            printf("p2 -> left\n");
        else if (outcode == 3)
            printf("p2 -> derriere\n");
        else
            printf("p2 -> inside\n");
    }
}
