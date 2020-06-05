#ifndef TEST_H
#define TEST_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <limits.h>
# include <strings.h>

#define TWOSIDED 4

typedef float			    t_vecf2 __attribute__((ext_vector_type(2)));
typedef unsigned char		t_u16;
typedef struct s_map        t_map;
typedef struct s_sector     t_sector;
typedef struct s_polygon    t_polygon;
typedef struct s_line       t_line;
typedef struct s_lst_line   t_lst_line;
typedef struct s_divline    t_divline;
typedef struct s_bspnode    t_bspnode;

struct s_polygon
{
    int         n;
    t_vecf2     p1;
    t_vecf2     p2;
    int         high;
    int         mod;
    int         flags;//backside will not be present at all if not two sided
    int         sector;
};

struct s_divline
{
    t_vecf2     p;
    float       dx;
    float       dy;
};

struct s_line
{
    t_vecf2         p1;
    t_vecf2         p2;
    int             side;//bord de secteur 1
    int             linedef;
    int             offset;
    int             flags;//transparence ex
    int             sector;
    bool            grouped;//pour ne pas etre pris en compte deux fois
};

struct s_lst_line
{
    t_line          lst[256];
    int             count;
};

struct s_bspnode
{
	//float				bbox[4];
    t_line              line;
    t_divline           divline;
    struct s_bspnode    *side[2];
};

struct s_sector
{
    int         h_ceil;
    int         h_floor;
    int         n_neighboor;
    t_bspnode   *bsp;
    t_sector    **neighboors;
    t_texture   *wall;
    t_texture   *ceil;
    t_texture   *floor;
};

struct s_map
{
    int         nb_sectors;
    int         *z_buffer[2];
    t_bspnode   *lines;
    t_sector    sectors[];
};

void        make_divlinefromworld(t_divline *dvl, t_line *l);
float       equation_plan(t_divline *v1, t_divline *v2);
float       cross_plan(t_divline *v1, t_divline *v2);
float       norm_plan(t_divline *v);
float       intersectvector(t_divline *v1, t_divline *v2);
int         sign(float i);
float       float_round(float x);
int         pointonside(t_vecf2 pt, t_divline *dvl);
int         lineonside(t_line *l, t_divline *dvl);
t_line      cutline(t_line *wl, t_divline *dvl, int *cuts);
int         evaluate_split(t_lst_line *lines, t_line *spliton, int bestgrade,
    int grade);
void        execute_split(t_lst_line *lines, t_line *spliton, t_lst_line *frontlist,
    t_lst_line *backlist, int *cuts);
//t_line     lresearch(t_lst_line *lines, int *bestv, int step);
//void    lresearch(t_lst_line *lines, t_line *bestline, int *bestv, int step);
void        cpy_line(t_line *dest, t_line *src);
t_bspnode   *bspbuild(t_lst_line *lines, int *cuts);
void        make_seg(t_lst_line *lines, t_polygon origine[256], int nseg);
void        make_bsp(t_polygon lst_p[256], int nseg);

void        print_bsp(t_bspnode *bsp);


#endif
