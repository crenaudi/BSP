#include "../include/bsp.h"

int     evaluate_split(t_lst_line *lines, t_line *spliton, int bestgrade, int grade)
{
    t_divline   dvl;
    t_line      line_p;
    int         nfront;
    int         nback;
    int         info[3];

    nfront = 0;
    nback = 0;
    info[0] = -1;
    make_divlinefromworld(&dvl, spliton);
    while (++info[0] < lines->count)
    {
        line_p = lines->lst[info[0]];
        if (&line_p == spliton)
            info[1] = 0;
        else
            info[1] = lineonside(&line_p, &dvl);
        if (info[1] == 0)
            nfront++;
        if (info[1] == 1)
            nback++;
        if (info[1] == -2)
        {
            nfront++;
            nback++;
        }
        info[2] = (nfront + nback) - lines->count;
        grade = (((nfront > nback) ? nfront : nback) + info[2]) * 8;
        if (grade > bestgrade)
            return (grade);
    }
    return ((nfront == 0 || nback == 0) ? INT_MAX : grade);
}

t_line  cutline(t_line *wl, t_divline *dvl, int *cuts)
{
    t_line      new;
    t_divline   tmp;
    int         offset;
    t_vecf2     intersect;
    float       frac;


    *cuts += 1;
    make_divlinefromworld(&tmp, wl);
    bzero(&new, sizeof(t_line));
    new = *wl;
    frac = intersectvector(&tmp, dvl); // if == 0 printf("error intersect : vector are parallel or outside line");
    intersect.x = tmp.p.x + float_round(tmp.dx * frac);
    intersect.y = tmp.p.y + float_round(tmp.dy * frac);
    offset = wl->offset + roundf(frac * norm_plan(&tmp));
    if (pointonside(wl->p1, dvl) == 0)
    { //front
        wl->p2 = intersect;
        new.p1 = intersect;
        new.offset = offset;
    }
    else
    { //back
        wl->p1 = intersect;
        wl->offset = offset;
        new.p2 = intersect;
    }
    return (new);
}

void    execute_split(t_lst_line *lines, t_line *spliton,
    t_lst_line *frontlist, t_lst_line *backlist, int *cuts)
{
    int         i;
    int         side;
    t_line      line_p;
    t_line      new_p;
    t_divline   dvl;

    i = -1;
    make_divlinefromworld(&dvl, spliton);
    while (++i < lines->count)
    {
        line_p = lines->lst[i];
        if (!(line_p.p1.x == spliton->p1.x && line_p.p1.y == spliton->p1.y
            && line_p.p2.x == spliton->p2.x && line_p.p2.y == spliton->p2.y))
        {
            side = lineonside(&line_p, &dvl);
            if (side == 0)
            {
                cpy_line(&frontlist->lst[frontlist->count], &line_p);
                frontlist->count += 1;
            }
            else if (side == 1)
            {
                cpy_line(&backlist->lst[backlist->count], &line_p);
                backlist->count += 1;
            }
            else if (side == -2)
            {
                new_p = cutline(&line_p, &dvl, cuts);
                cpy_line(&frontlist->lst[frontlist->count], &line_p);
                frontlist->count += 1;
                cpy_line(&backlist->lst[backlist->count], &new_p);
                backlist->count += 1;
            }
        }
    }
}
/*
printf("front %d (%f,%f)(%f,%f)\n", frontlist->lst[frontlist->count].linedef,
    frontlist->lst[frontlist->count].p1.x, frontlist->lst[frontlist->count].p1.y,
    frontlist->lst[frontlist->count].p2.x, frontlist->lst[frontlist->count].p2.y);
    */
