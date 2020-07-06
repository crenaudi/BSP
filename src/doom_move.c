#include "../include/bsp.h"

t_vecf2			get_newpos(t_vecf2 dir, t_vecf2 coord)
{
	t_vecf2	new;
    /*
	if (dir.x > 0.0 && map.data[(int)coord.y][(int)(coord.x + DIST)])
		dir.x = 0;
	else if (dir.x < 0.0 && map.data[(int)coord.y][(int)(coord.x - DIST)])
		dir.x = 0;
	if (dir.y > 0.0 && map.data[(int)(coord.y + DIST)][(int)coord.x])
		dir.y = 0;
	else if (dir.y < 0.0 && map.data[(int)(coord.y - DIST)][(int)coord.x])
		dir.y = 0;
    */
	new = coord + dir;
	//if ()
		return (new);
	//return (coord);
}

static float	get_angle(int x, int y)
{
	if (x && y)
		return (((x == 1) ? 1 : 3) * (API / 4) * (float)(y));
	else if (x)
		return ((x == 1) ? 0 : API);
	else
		return (API / 2.0 * (float)y);
}

int				move_player(t_player *pl, float x, float y, float speed)
{
	t_vecf2		newpos;
	float		angle;

	if (!x && !y)
		return (ERROR);
	angle = get_angle(x, y);
	newpos.x = cos(pl->eyes_dirx + angle) * speed;
    newpos.y = -1 * sin(pl->eyes_dirx + angle) * speed;
	newpos = get_newpos(newpos, (t_vecf2){pl->x, pl->y});
	pl->x = newpos.x;
	pl->y = newpos.y;
	return (SUCCESS);
}

 static void move_camera(t_engine *e, t_player *pl, float speed)
 {
    if (e->key_right == 1)
 	{
 		pl->eyes_dirx += speed;
 		if (pl->eyes_dirx > TWOPI)
 			pl->eyes_dirx -= TWOPI;
 	}
 	if (e->key_left == 1)
 	{
 		pl->eyes_dirx -= speed;
 		if (pl->eyes_dirx < 0)
 			pl->eyes_dirx += TWOPI;
 	}
 }

void check_move(t_engine *e)
{
    int x;
    int y;

    x = 0;
    y = 0;
    if (e->key_a == 1)
		x = -1;
	if (e->key_d == 1)
		x = 1;
    if (e->key_w == 1)
		y = -1;
	if (e->key_s == 1)
		y = 1;
    move_camera(e, e->player, 0.01);
    move_player(e->player, x, y, 0.1);
    update_cam2d(&e->player->cam, e->player->x, e->player->y,
		e->player->eyes_dirx, e->xplan);
}
