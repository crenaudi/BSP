#include "../include/bsp.h"

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

int     pointonside(t_vecf2 pt, t_divline *dvl)
{
    float   dx;
    float   dy;
    float   left;
    float   right;
    float   a;
    float   b;
    float   c;
    float   d;

    if (!dvl->dx) //seg aligné en x
    {
        if (pt.x > dvl->p.x - 2 && pt.x < dvl->p.x + 2)
            return (-1); //colinear
        return ((pt.x < dvl->p.x) ? dvl->dy > 0 : dvl->dy < 0);
        //vrai 1 back
        //false 0 front
    }
    if (!dvl->dy) //seg aligné en y
    {
        if (pt.y > dvl->p.y - 2 && pt.y < dvl->p.y + 2)
            return (-1); //colinear
        return ((pt.y < dvl->p.y) ? dvl->dx < 0 : dvl->dx > 0);
        //vrai 1 back
        //false 0 front
    }

    //equation de plan :
    dx = pt.x - dvl->p.x;
    dy = pt.y - dvl->p.y;
    left = dvl->dy * dx;
    right = dy * dvl->dx;

    if (fabs(left - right) < 0.5)
        return (-1); //on line
    return ((right < left) ? 0 /* front */ : 1 /* back */);
}

int lineonside(t_line *l, t_divline *dvl)
{
    int     s1;
    int     s2;

    s1 = pointonside(l->p1, dvl);
    s2 = pointonside(l->p2, dvl);
    // 0 front 1 back -1 colinear / on line
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