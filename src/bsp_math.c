#include "../include/bsp.h"

float	distfrom(float x0, float y0, float x1, float y1)
{
	float 	x;
	float	y;

	x = x1 - x0;
	y = y1 - y0;
	return (sqrtf(x * x + y * y));
}

int     sign(float i)
{
	if (i < 0)
		return -1;
	else if ( i > 0)
		return 1;
	return 0;
}

float     float_round(float x)
{
	if (x > 0)
	{
		if (x - (int)x < 0.1)
			return ((float)((int)x));
		else if (x - (int)x > 0.9)
			return ((float)((int)x + 1));
		else
			return (x);
	}
	if ((int)x - x < 0.1)
		return ((float)((int)x));
	else if ((int)x - x > 0.9)
		return ((float)((int)(x) - 1));
	return (x);
}

static int     pointonside_suite(t_vecf3 pt, t_divline *dvl)
{
    float   dx;
    float   dy;
	float	check[4];

	//equation de plan :
    dx = dvl->p.x - pt.x;
    dy = dvl->p.y - pt.y;

	check[0] = dvl->dx * dvl->dx + dvl->dy * dvl->dy;
	check[1] = 2 * (dvl->dx * dx + dvl->dy * dy);
	check[2] = dx * dx + dy * dy - 2 * 2;		// 2 unit radius
	check[3] = check[1] * check[1] - 4 * check[0] * check[2];
	if (check[3] > 0)
		return (ERROR);
	return (SUCCESS);
}

int     pointonside(t_vecf3 pt, t_divline *dvl)
{
    float   dx;
    float   dy;
    float   left;
    float   right;

    if (!dvl->dx) //seg aligné en x
    {
        if (pt.x > dvl->p.x - .2 && pt.x < dvl->p.x + .2)//2
            return (-1); //colinear
        return ((pt.x < dvl->p.x) ? dvl->dy > 0 : dvl->dy < 0);//vrai 1 back //false 0 front
    }
    if (!dvl->dy) //seg aligné en y
    {
        if (pt.y > dvl->p.y - .2 && pt.y < dvl->p.y + .2)
            return (-1); //colinear
        return ((pt.y < dvl->p.y) ? dvl->dx < 0 : dvl->dx > 0);//vrai 1 back//false 0 front
    }
	if (pointonside_suite(pt, dvl) == ERROR)
		return (-1);
	dx = pt.x - dvl->p.x;
	dy = pt.y - dvl->p.y;
    left = dvl->dy * dx;
    right = dy * dvl->dx;
    if (fabs(left - right) < 0.05)//.5
        return (-1); //on line
    return ((right < left) ? 0 /* front */ : 1 /* back */);
}

int lineonside(t_line *l, t_divline *dvl)
{
    int     s1;
    int     s2;

    s1 = pointonside(l->p1, dvl);
    s2 = pointonside(l->p2, dvl); // 0 front 1 back -1 colinear / on line
    if (s1 == s2) // tous les deux front ou back ou colinéaire
    {
        if (s1 == -1) // s1 colinear
        {
            if (sign(l->p2.x - l->p1.x) == sign(dvl->dx)
                && sign(l->p2.y - l->p1.y) == sign(dvl->dy))
                return (0);//colinear in same direction
            return (1);//colinear none same direction
        }
        return (s1);
    }
    if (s1 == -1)
		return (s2); //s1 colineaire donc on voit si s2 front ou back
	if (s2 == -1)
		return (s1);//s2 colineaire donc on voit si s1 front ou back
	return (-2); // par deduction on sait que les segments se croise
}
