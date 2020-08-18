#include "../include/bsp.h"

static t_vecf3 cut_right(t_line *line, t_cam2d c)
{
    float       frac;
    t_vecf3     new;
    t_divline   tmp;
    t_divline   frustrum;

    make_divline(&tmp, line->p1, line->p2);
    frustrum.p = c.dvl_lr.p;
    frustrum.dx = c.depthright.x - c.dvl_lr.p.x;
    frustrum.dy = c.depthright.y - c.dvl_lr.p.y;
    frac = intersect_vector(&tmp, &frustrum);
    new.x = tmp.p.x + float_round(tmp.dx * frac);
    new.y = tmp.p.y + float_round(tmp.dy * frac);
    new.z = tmp.p.z;
    return (new);
}

static t_vecf3 cut_left(t_line *line, t_player *pl)
{
    float       frac;
    t_vecf3     new;
    t_divline   tmp;
    t_divline   frustrum;

    make_divline(&tmp, line->p1, line->p2);
    frustrum.p = (t_vecf3){pl->x, pl->y, 0};
    frustrum.dx = pl->cam.depthleft.x - pl->x;
    frustrum.dy = pl->cam.depthleft.y - pl->y;
    frac = intersect_vector(&tmp, &frustrum);
    new.x = tmp.p.x + float_round(tmp.dx * frac);
    new.y = tmp.p.y + float_round(tmp.dy * frac);
    new.z = tmp.p.z;
    return (new);
}

static t_vecf3 cut_bottom(t_line *line, t_cam2d c)
{
    float       frac;
    t_vecf3     new;
    t_divline   tmp;
    t_divline   frustrum;

    make_divline(&tmp, line->p1, line->p2);
    frustrum.p = (t_vecf3){c.depthleft.x, c.depthleft.y, 0};
    frustrum.dx = c.depthright.x - c.depthleft.x;
    frustrum.dy = c.depthright.y - c.depthleft.y;
    frac = intersect_vector(&tmp, &frustrum);
    new.x = tmp.p.x + float_round(tmp.dx * frac);
    new.y = tmp.p.y + float_round(tmp.dy * frac);
    new.z = tmp.p.z;
    return (new);
}

static void find_p1(t_line *line, t_player *pl)
{
    int outcode0;
    int outcode1;
    t_vecf3 p1;

    outcode0 = pointonside(line->p1, &pl->cam.dvl_lr);
    outcode1 = pointonside(line->p1, &pl->cam.dvl_fb);
    if (outcode1 == 0)
    {
        if (outcode0 == 1)
        {
            printf("p1 right -\n");
            p1 = cut_right(line, pl->cam);
            line->angle1 = pl->cam.amin;
        }
        else
        {
            printf("p1 left +\n");
            p1 = cut_left(line, pl);
            line->angle1 = pl->cam.amax;
        }
    }
    else
    {
        p1 = cut_bottom(line, pl->cam);
        line->angle1 = add_angle4vector(line->p1.x, line->p1.y, pl);
    }
    line->p1 = p1;
}

static void find_p2(t_line *line, t_player *pl)
{
    int outcode0;
    int outcode1;
    t_vecf3 p2;

    outcode0 = pointonside(line->p2, &pl->cam.dvl_lr);
    outcode1 = pointonside(line->p2, &pl->cam.dvl_fb);
    if (outcode1 == 0)
    {
        if (outcode0 == 1)
        {
            printf("p2 right -\n");
            p2 = cut_right(line, pl->cam);
            line->angle2 = pl->cam.amin;
        }
        else
        {
            printf("p2 left +\n");
            p2 = cut_left(line, pl);
            line->angle2 = pl->cam.amax;
        }
    }
    else
    {
        p2 = cut_bottom(line, pl->cam);
        line->angle2 = add_angle4vector(line->p2.x, line->p2.y, pl);
    }
    line->p2 = p2;
}

void precompute(t_engine *e, t_lst_line *lstlines, t_player *pl)
{
    int     i;
    float   tmp;
    t_line  *line;

    i = -1;
    while (++i < lstlines->count)
    {
        line = &lstlines->lst[i];
        if (evaluate_pointonview(pl->cam, pl->cam.dvl_lr, line->p1.x,
            line->p1.y) == SUCCESS)
            line->angle1 = add_angle4vector(line->p1.x, line->p1.y, pl);
        else
            find_p1(line, pl);
        if (evaluate_pointonview(pl->cam, pl->cam.dvl_lr, line->p2.x,
            line->p2.y) == SUCCESS)
            line->angle2 = add_angle4vector(line->p2.x, line->p2.y, pl);
        else
            find_p2(line, pl);
        if (line->angle2 < line->angle1)
        {
            tmp = line->angle1;
            line->angle1 = line->angle2;
            line->angle2 = tmp;
        }
        lstlines->leq[i].p = line->p1;
        lstlines->leq[i].dx = line->p2.x - line->p1.x;
        lstlines->leq[i].dy = line->p2.y - line->p1.y;
        precompute_linear_equation(&lstlines->leq[i], pl->x, pl->y);
    }
    raycast(e, pl, lstlines);
}
