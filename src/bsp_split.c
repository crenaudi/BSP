#include "../include/bsp.h"

int     evaluate_split(t_lst_line *lines, t_line *spliton, int bestgrade, int grade)
{
    t_divline   dvl;
    t_line      line_p;
    int         nfront;
    int         nback;
    int         new_seg;
    int         side;
    int         i;

    make_divlinefromworld(&dvl, spliton);
    nfront = 0;
    nback = 0;
    i = -1;
    while (++i < lines->count)
    {
        line_p = lines->lst[i];
        if (&line_p == spliton)
            side = 0; //same seg
        else
            side = lineonside(&line_p, &dvl);
        if (side == 0)
            nfront++;
        if (side == 1)
            nback++;
        if (side == -2)
        {
            nfront++;
            nback++;
        }
        new_seg = (nfront + nback) - lines->count;
        grade = (((nfront > nback) ? nfront : nback) + new_seg) * 8;
        if (grade > bestgrade)
            return (grade);
    }
    if (nfront == 0 || nback == 0)
        return (INT_MAX);
    return (grade);
}

t_line  cutline(t_line *wl, t_divline *dvl, int *cuts)
{
    t_line      new;
    t_divline   tmp;
    float       frac;
    t_vecf2     intersect;
    int         offset;

    *cuts += 1;
    make_divlinefromworld(&tmp, wl);
    bzero(&new, sizeof(t_line));
    new = *wl;
    if ((frac = intersectvector(&tmp, dvl)) == 0)
        printf("error intersect : vector are parallel or outside line");
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

    make_divlinefromworld(&dvl, spliton);
    i = -1;
    while (++i < lines->count)
    {
        line_p = lines->lst[i];
        if (line_p.p1.x == spliton->p1.x && line_p.p1.y == spliton->p1.y
            && line_p.p2.x == spliton->p2.x && line_p.p2.y == spliton->p2.y)
            printf("spliton\n");
        else
        {
            side = lineonside(&line_p, &dvl);
            if (side == 0)
            {
                cpy_line(&frontlist->lst[frontlist->count], &line_p);
                printf("front %d (%f,%f)(%f,%f)\n", frontlist->lst[frontlist->count].linedef,
                    frontlist->lst[frontlist->count].p1.x, frontlist->lst[frontlist->count].p1.y,
                    frontlist->lst[frontlist->count].p2.x, frontlist->lst[frontlist->count].p2.y);
                frontlist->count += 1;
            }
            else if (side == 1)
            {
                cpy_line(&backlist->lst[backlist->count], &line_p);
                printf("back %d (%f,%f)(%f,%f)\n", backlist->lst[backlist->count].linedef,
                    backlist->lst[backlist->count].p1.x, backlist->lst[backlist->count].p1.y,
                    backlist->lst[backlist->count].p2.x, backlist->lst[backlist->count].p2.y);
                backlist->count += 1;
            }
            else if (side == -2)
            {
                new_p = cutline(&line_p, &dvl, cuts);

                cpy_line(&frontlist->lst[frontlist->count], &line_p);
                printf("side -2 front %d (%f,%f)(%f,%f)\n", frontlist->lst[frontlist->count].linedef,
                    frontlist->lst[frontlist->count].p1.x, frontlist->lst[frontlist->count].p1.y,
                    frontlist->lst[frontlist->count].p2.x, frontlist->lst[frontlist->count].p2.y);
                frontlist->count += 1;

                cpy_line(&backlist->lst[backlist->count], &new_p);
                printf("side -2 back %d (%f,%f)(%f,%f)\n", backlist->lst[backlist->count].linedef,
                    backlist->lst[backlist->count].p1.x, backlist->lst[backlist->count].p1.y,
                    backlist->lst[backlist->count].p2.x, backlist->lst[backlist->count].p2.y);
                backlist->count += 1;
            }
        }
    }
}
