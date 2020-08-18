#include "../include/bsp.h"

static void	putpixel(t_img *img, t_vec2 i, t_vec2 size, int color)
{
	int	index;

	printf("at : %d, %d\ncolor : %d\n", i.x, i.y, color);
	index = i.x + i.y * size.x;
	if (index < 0 || index >= size.x * size.y)
		return ;
	img->data[index] = color;
}

void draw_col(t_engine *e, int x, int start, int end, float dist, int nbline)
{
    int color;
	int i;

	i = -1;
	printf("nb line %d\n", nbline);
	(void)dist;
	while (++i < start)
	{
		color = 0x383838;
		putpixel(e->img, (t_vec2){x, i}, (t_vec2){e->xplan, e->yplan}, color);
	}
    while (start++ <= end)
    {
        if (nbline == 1)
			color = 0x000000;//noir
		if (nbline == 2)
			color = 0xFFFFFF;//blanc
		if (nbline == 3)
			color = 0xe5989b;//rose
		if (nbline == 4)
			color = 0xe63946;//rouge
		if (nbline == 5)
			color = 0xa8dadc;//bleu claire
		if (nbline == 6)
			color = 0x1d3557;//bleu fonce
		if (nbline == 7)
			color = 0x90be6d;//vert
		if (nbline == 8)
			color = 0xbc6c25;//marron
		if (nbline == 9)
			color = 0x8338ec;//violet
		if (nbline == 10)
			color = 0x457b9d;//bleu medium
		if (nbline == 11)
			color = 0x9e0059;//prune
		if (nbline == 12)
			color = 0x390099;//encre
		if (nbline == 13)
			color = 0xe76f51;//orange
		if (nbline == 14)
			color = 0xe9c46a;//jaune
        //printf("%d %d color %d\n", x, start, color);
        putpixel(e->img, (t_vec2){x, start}, (t_vec2){e->xplan, e->yplan}, color);
    }
	while (++end < e->yplan)
	{
		color = 0x606D5D;
		putpixel(e->img, (t_vec2){x, end}, (t_vec2){e->xplan, e->yplan}, color);
	}
}
