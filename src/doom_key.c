#include "../include/bsp.h"

int		key_press(int key, t_engine *e)
{
	if (key == K_ARIGHT)
		e->key_right = 1;
	if (key == K_ALEFT)
		e->key_left = 1;
	if (key == K_W)
		e->key_w = 1;
	if (key == K_S)
		e->key_s = 1;
	if (key == K_A)
		e->key_a = 1;
	if (key == K_D)
		e->key_d = 1;
	if (key == K_SPC)
		e->key_shoot = 1;
	if (key == K_ESC)
	   close_engine(e);
	return (SUCCESS);
}

int		key_release(int key, t_engine *e)
{
	if (key == K_ARIGHT)
		e->key_right = 0;
	if (key == K_ALEFT)
		e->key_left = 0;
	if (key == K_W)
		e->key_w = 0;
	if (key == K_S)
		e->key_s = 0;
	if (key == K_A)
		e->key_a = 0;
	if (key == K_D)
		e->key_d = 0;
	if (key == K_SPC)
		e->key_shoot = 0;
	if (key == K_ESC)
		close_engine(e);
	return (SUCCESS);
}
