#ifndef BSP_H
#define BSP_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <limits.h>
# include <strings.h>
# include "mlx.h"
# include "libft.h"
# include "gfx.h"

# define WIDTH      800
# define HEIGHT     600
# define TWOSIDED   4
# define MAXWALL    256
# define MAXSPRITE  128
# define API		3.1415927
# define API_4		0.7853982
# define API_34		2.3561945
# define TWOPI		6.2831854

#define BOXLEFT     0
#define BOXRIGHT    1
#define BOXTOP      2
#define BOXBOTTOM   3

# define SUCCESS	0
# define ERROR		-1

typedef struct s_map        t_map;
typedef struct s_sector     t_sector;
typedef struct s_line       t_line;
typedef struct s_lst_line   t_lst_line;
typedef struct s_linear_eq  t_linear_eq;
typedef struct s_bspnode    t_bspnode;
typedef struct s_player     t_player;
typedef struct s_engine     t_engine;
typedef struct s_global     t_global;

struct s_line
{
    t_vecf3         p1;
    t_vecf3         p2;
    float           ground;
    int             twoside;
    int             linedef;
    float           offset;
    int             flags;//transparence ex
    int             sector;
    float           angle1;
    float           angle2;
};

struct s_linear_eq
{
    float           plan;
    float           dist;
	float           dx;
	float           dy;
    t_vecf3         p;
    t_vecf4         xprime;
    t_vecf4         yprime;
    t_vecf2         pprime;
};

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

struct s_lst_line
{
    int             count;
    t_line          lst[256];
    t_linear_eq     leq[256];
};

struct s_bspnode
{
    t_line              line;
    t_divline           divline;
    struct s_bspnode    *side[2];
};

struct s_sector
{
    float       h_ceil;
    float       h_floor;
    //t_obj       obj[];//128 max
    t_texture   *wall;
    t_texture   *ceil;
    t_texture   *floor;
};

struct s_map
{
    int         nb_sectors;
    t_bspnode   *bsp;
    //t_sector    sectors[];
};

struct			s_player
{
	float	    x;
	float	    y;
	float		eyes_dirx;
    float       eyes_diry;
    int         eyes_height;
    int         height;
    t_cam2d		cam;
};

struct			s_global
{
	t_player	player;
    t_map		map;
};


struct			s_engine
{
    void		*mlx_ptr;
	void		*win_ptr;
    t_global    global;
    t_player	*player;
    t_map		*map;
    t_img		*img;
	t_img		*srcs[2];
    int         nsrc;
	int         xplan;
	int         yplan;
	int         half_xplan;
    int         half_yplan;
    short       key_right;
    short       key_left;
    short       key_w;
    short       key_s ;
    short       key_a;
    short       key_d;
    short       key_shoot;
};

/*******************************************************************************
    MATH FUNCTION
*******************************************************************************/

float	    distfrom(float x0, float y0, float x1, float y1);
int         sign(float i);
float       float_round(float x);
int         pointonside(t_vecf3 pt, t_divline *dvl);
int         lineonside(t_line *l, t_divline *dvl);
float		evaluate_pointonview(t_cam2d c, float x, float y);
int         seg_onview(t_cam2d c, t_line *line, t_vecf2 depth);
void        precompute_linear_equation(t_linear_eq *leq, float plx, float ply);
void        execute_linear_equation(t_linear_eq *leq, float plx, float ply,
    float a);

/*******************************************************************************
    INIT FUNCTION
*******************************************************************************/

void		init_engine(t_engine *e, t_lst_line *polygons);
t_player    init_player(void);
t_map		init_map(t_engine *e, t_lst_line *polygons, int nb_sectors);
void        init_lstline(t_lst_line *lines);
void        init_2lstline(t_lst_line *lst1, t_lst_line *lst2);
t_bspnode   *init_node();
void        add_polygon2list(t_lst_line *lines, t_vecf3 p1, t_vecf3 p2,
    int flags, int sector);
void        precompute(t_engine *e, t_lst_line *lstlines, t_player *pl);
void		init_global(t_global *global, t_engine *e, t_lst_line *polygons);

/*******************************************************************************
    BUILD BSP FUNCTION
*******************************************************************************/

t_line      cutline(t_line *wl, t_divline *dvl);
int         evaluate_split(t_lst_line *lines, t_line *splt, int bestgrade,
    int grade);
void        execute_split(t_lst_line *lines, t_line *spliton,
    t_lst_line *frontlist, t_lst_line *backlist);
void        cpyl(t_line *dest, t_line *src);
t_bspnode   *bspbuild(t_lst_line *lines);
void        walk_tree(t_bspnode *node, t_cam2d c, t_lst_line *p_lines,
    t_vecf2 depth);
void        bsp_renderer(t_engine *e, t_player *pl, t_bspnode *node);

/*******************************************************************************
    CLOSE
*******************************************************************************/

void		close_map(t_map *map);
void        close_bsp(t_bspnode *node);
void		close_engine(t_engine *e);
int         close_hook(t_engine *e);
void        doom_error(t_engine *e, unsigned int err, char *line);

/*******************************************************************************
    DOOM_TEST
*******************************************************************************/

void	   raycast(t_engine *e, t_player *pl, t_lst_line *lines);
int		   key_press(int key, t_engine *e);
int		   key_release(int key, t_engine *e);
void       draw_col(t_engine *e, int x, int start, int end, float dist);
void       check_move(t_engine *e);

#endif
