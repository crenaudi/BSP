#include "../include/bsp.h"

static int compute_outcode(float x, float y, foat frustrum[4])
{
	int code;

	code = INSIDE;
	if (x < frustrum[BOXLEFT])
		code |= LEFT;
	else if (x > frustrum[BOXRIGHT])
		code |= RIGHT;
	if (y < frustrum[BOXBOTTOM])
		code |= BOTTOM;
	else if (y > frustrum[BOXTOP])
		code |= TOP;
	return code;
}

static t_vecf2	compute_xy(t_vecf3 p1, t_vecf3 p2, float frustrum[4])
{
	float 	x;
	float	y;

	if (outcodeOut & TOP)
	{
		x = p1.x + (p2.x - p1.x) * (frustrum[BOXTOP] - p1.y) / (p2.y - p1.y);
		y = frustrum[BOXTOP];
	}
	else if (outcodeOut & BOTTOM)
	{
		x = p1.x + (p2.x - p1.x) * (frustrum[BOXBOTTOM] - p1.y) / (p2.y - p1.y);
		y = frustrum[BOXBOTTOM];
	}
	else if (outcodeOut & RIGHT)
	{
		y = p1.y + (p2.y - p1.y) * (frustrum[BOXRIGHT] - p1.x) / (p2.x - p1.x);
		x = frustrum[BOXRIGHT];
	}
	else if (outcodeOut & LEFT)
	{
		y = p1.y + (p2.y - p1.y) * (frustrum[BOXLEFT] - p1.x) / (p2.x - p1.x);
		x = frustrum[BOXLEFT];
	}
	return ((t_vecf2){x, y});
}

int cohensutherland_lineclip(t_line *line, t_lst_line *p_lines, t_cam2d *c)
{
	int 	outcode[2]
	int		outcodeout;
	t_vecf3	p1;
	t_vecf3	p2;
	t_vecf2	ret;

	p1 = line->p1;
	p2 = line->p2;
	outcode[0] = compute_outcode(p1.x, p1.y, c->frustrum);
	outcode[1] = compute_outcode(p2.x, p2.y, c->frustrum);
	while (1)
	{
		if (!(outcode[0] | outcode[1]))
		{
			cpy4print();
			return (SUCCESS);
		}
		else if (outcode[0] & outcode[1])
			return (ERROR);
		else
		{
			outcodeout = (outcode[1] > outcode[0]) ? outcode[1] : outcode[0];
			ret = compute_xy(p1, p2, frustrum[4]);
			if (outcodeout == outcode[0])
			{
				p1.x = ret.x;
				p1.y = ret.y;
				outcode0 = compute_outcode(p1.x, p1.y);
			}
			else
			{
				p2.x = ret.x;
				p2.y = ret.y;
				outcode1 = compute_outcode(p2.x, p2.y);
			}
		}
	}
}
