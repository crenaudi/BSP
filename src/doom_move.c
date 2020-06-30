#include "../include/bsp.h"

 static void move_player(t_player *pl, int x, int y, float speed)
 {
    if (x != 0)
        pl->x += (x > 0) ? speed : -speed;
    if (y != 0)
        pl->y += (y > 0) ? speed : -speed;
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
    update_cam2d(&pl->cam, pl->x, pl->y, pl->eyes_dirx);
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

    move_player(e->player, x, y, 0.06);
    move_camera(e, e->player, 0.06);
}
