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

static void find_p1(t_line *line, t_info_line *linfo, t_player *pl)
{
    int outcode0;
    int outcode1;

    outcode0 = pointonside(line->p1, &pl->cam.dvl_lr);
    outcode1 = pointonside(line->p1, &pl->cam.dvl_fb);
    if (outcode1 == 0)
    {
        if (outcode0 == 1)
        {
            line->p1 = cut_right(line, pl->cam);
            line->angle1 = pl->cam.amin;
        }
        else
        {
            line->p1 = cut_left(line, pl);
            line->angle1 = pl->cam.amax;
        }
    }
    else
    {
        line->p1 = cut_bottom(line, pl->cam);
        line->angle1 = evaluate_pointonview(pl->cam,
            line->p1.x, line->p1.y);
    }
    linfo->d1 = distfrom(line->p1.x, line->p1.y, pl->x, pl->y);
}

static void find_p2(t_line *line, t_info_line *linfo, t_player *pl)
{
    int outcode0;
    int outcode1;

    outcode0 = pointonside(line->p2, &pl->cam.dvl_lr);
    outcode1 = pointonside(line->p2, &pl->cam.dvl_fb);
    if (outcode1 == 0)
    {
        if (outcode0 == 1)
        {
            line->p2 = cut_right(line, pl->cam);
            line->angle2 = pl->cam.amin;
        }
        else
        {
            line->p2 = cut_left(line, pl);
            line->angle2 = pl->cam.amax;
        }
    }
    else
    {
        line->p2 = cut_bottom(line, pl->cam);
        line->angle2 = evaluate_pointonview(pl->cam,
            line->p2.x, line->p2.y);
    }
    linfo->d2 = distfrom(line->p2.x, line->p2.y, pl->x, pl->y);
}

void precompute(t_engine *e, t_lst_line *lstlines, t_player *pl)
{
    int             i;
    t_line          *line;
    t_info_line     info[255];

    i = -1;
    while (++i < lstlines->count)
    {
        line = &lstlines->lst[i];
        if (line->angle1 == 0)
            find_p1(line, &info[i], pl);
        if (line->angle2 == 0)
            find_p2(line, &info[i], pl);
        if (line->angle2 < line->angle1)
        {
            line->angle1 += line->angle2;
            line->angle2 = line->angle1 - line->angle2;
            line->angle1 = line->angle1 - line->angle2;
            info[i].d1 += info[i].d2;
            info[i].d2 = info[i].d1 - info[i].d2;
            info[i].d2 = info[i].d1 - info[i].d2;
        }
    }
    raycast(e, pl, lstlines, info);
}
/*
printf("\nLINE %d :\n", line->linedef);
printf("p1 -> %f, %f\np2 -> %f, %f\nangle1 -> %f\nangle2 -> %f\n",
    line->p1.x, line->p1.y, line->p2.x, line->p2.y, line->angle1, line->angle2);
printf("p1 -> %f, %f\np2 -> %f, %f\nangle1 -> %f\nangle2 -> %f\n",
    line->p1.x, line->p1.y, line->p2.x, line->p2.y, line->angle1, line->angle2);
*/
