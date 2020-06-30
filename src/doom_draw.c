#include "../include/bsp.h"

static void	putlepx(t_img *img, t_vec2 i, t_vec2 size, int color)
{
	int	index;

	index = i.x + i.y * size.x;
	if (index < 0 || index >= size.x * size.y)
		return ;
	img->data[index] = color;
}

void draw_col(t_engine *e, int x, int start, int end, float dist)
{
    int color;

    while (start++ <= end)
    {
        if (dist > 80.f)
            color = 0x777777;
        else if (dist > 60.f)
            color = 0x999999;
        else if (dist > 40.f)
            color = 0xBBBBBB;
        else if (dist > 20.f)
            color = 0xDDDDDD;
        else
            color = 0xFFFFFF;
        //printf("%d %d color %d\n", x, start, color);
        putlepx(e->img, (t_vec2){x, start}, (t_vec2){e->xplan, e->yplan}, color);
    }
}
