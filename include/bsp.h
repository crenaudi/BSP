#ifndef BSP_H
#define BSP_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <limits.h>
# include <strings.h>

# define SUCCESS		0
# define ERROR			-1
#define TWOSIDED   4
#define MAXWALL    256
#define MAXSPRITE  128
# define API		3.1415927
# define API_4		0.7853982
# define API_34		2.3561945
# define TWOPI		6.2831854

#define BOXLEFT     0
#define BOXRIGHT    1
#define BOXTOP      2
#define BOXBOTTOM   3

typedef float				t_vecf2 __attribute__((ext_vector_type(2)));
typedef float				t_vecf3 __attribute__((ext_vector_type(3)));
typedef unsigned char		t_u16;
typedef struct s_map        t_map;
typedef struct s_sector     t_sector;
typedef struct s_polygon    t_polygon;
typedef struct s_line       t_line;
typedef struct s_lst_line   t_lst_line;
typedef struct s_divline    t_divline;
typedef struct s_bspnode    t_bspnode;
typedef struct s_cam2d      t_cam2d;
typedef struct s_player     t_player;

struct s_polygon
{
    int         n;
    t_vecf3     p1;
    t_vecf3     p2;
    int         mod;
    int         flags;//backside will not be present at all if not two sided
    int         sector;
};

struct s_divline
{
    t_vecf3      p;
    float        dx;
    float        dy;
};

struct s_line
{
    t_vecf3         p1;
    t_vecf3         p2;
    float           ground;
    int             side;//bord de secteur 1
    int             linedef;
    /*
    offset  Size (bytes)
    0        2	     Partition line x coordinate
    2	     2	     Partition line y coordinate
    4	     2	     Change in x to end of partition line
    6	     2	     Change in y to end of partition line
    8	     8     	 Right bounding box
    16	     8	     Left bounding box
    24	     2	     Right child
    26	     2       Left child
    */
    float           offset;
    int             flags;//transparence ex
    int             sector;
    float   	    bbox[4];
    float           angle1;
    float           angle2;
    bool            grouped;//pour ne pas etre pris en compte deux fois
};

struct s_lst_line
{
    int             count;
    t_line          lst[256];
};

struct s_bspnode
{
    t_line              line;
    t_divline           divline;
    float 		        bbox[4];
    struct s_bspnode    *side[2];
};

struct s_sector
{
    float      h_ceil;
    float       h_floor;
    //t_obj       obj[];//128 max
    //t_texture   *wall;
    //t_texture   *ceil;
    //t_texture   *floor;
};

struct s_map
{
    int         nb_sectors;
    t_bspnode   *bsp;
    t_sector    sectors[];
};

struct					s_cam2d
{
	float		fov;
	float		half_fov;
    float       clipangle;
    float       depth;
    t_divline   dvl;
    /*
    t_divline   near;
    t_divline   far;
    t_divline   right;
    t_divline   left;
    */
};

struct			s_player
{
	float	    coord_x;
	float	    coord_y;
	float		eyes_dirx;
    float       eyes_diry;
    int         eyes_height;
    int         height;
    t_cam2d		cam;
};

/*******************************************************************************
    MATH FUNCTION
*******************************************************************************/

float       equation_plan(t_divline *v1, t_divline *v2);
float       cross_plan(t_divline *v1, t_divline *v2);
float       norm_plan(t_divline *v);
int         seg_onview(t_cam2d c, t_line line);
void        make_divlinefromworld(t_divline *dvl, t_line *l);
int         sign(float i);
float       float_round(float x);

int         pointonside(t_vecf3 pt, t_divline *dvl);
int         lineonside(t_line *l, t_divline *dvl);
float		evaluate_pointonview(t_cam2d c, float x, float y);
int         seg_onview(t_cam2d c, t_line line);

float       intersect_vector(t_divline *v1, t_divline *v2);
int         intersect_line(t_vecf2 x[2], t_vecf2 y[2], float tol);

/*******************************************************************************
    INIT FUNCTION
*******************************************************************************/

void        init_lstline(t_lst_line *lines);
void        init_2lstline(t_lst_line *lst1, t_lst_line *lst2);
t_bspnode   *init_node();
void        precompute(t_lst_line *lst, t_player *pl);

/*******************************************************************************
    BUILD FUNCTION
*******************************************************************************/

t_line      cutline(t_line *wl, t_divline *dvl);
int         evaluate_split(t_lst_line *lines, t_line *splt, int bestgrade,
    int grade);
    void    execute_split(t_lst_line *lines, t_line *spliton,
        t_lst_line *frontlist, t_lst_line *backlist);
void        cpyl(t_line *dest, t_line *src);
void        make_seg(t_lst_line *lines, t_polygon origine[256], int nseg);

void        clearbox(float box[4]);
void        addtobox(float box[4], float x, float y);

t_bspnode   *bspbuild(t_lst_line *lines);
t_bspnode   *make_bsp(t_polygon lst_p[256], int nseg, t_player *pl);
void        walk_tree(t_bspnode *node, t_cam2d c, t_lst_line *p_lines);
void        bsp_renderer(t_player *pl, t_bspnode *node);
void        close_bsp(t_bspnode *node);

/* V1
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
void        cpyl(t_line *dest, t_line *src);
void        make_seg(t_lst_line *lines, t_polygon origine[256], int nseg);
void        close_bsp(t_bspnode *node);
void        print_bsp(t_bspnode *bsp);
t_bspnode   *bspbuild(t_lst_line *lines, t_vecf2 pt, int *cuts);
t_bspnode   *make_bsp(t_polygon lst_p[256], int nseg, t_player *pl);
t_line      evaluate_closer(t_lst_line *lines, int bestdist, t_vecf2 pt);
float       dist_seg2point(t_vecf2 s1, t_vecf2 s2, t_vecf2 pt);
t_vecf2     point_closer2seg(t_vecf2 s1, t_vecf2 s2, t_vecf2 pt);
void        ray_renderer(t_player *pl, t_bspnode *node);
*/
#endif
