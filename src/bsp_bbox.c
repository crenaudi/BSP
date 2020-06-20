#include "../include/bsp.h"

void clearbox(float box[4])
{
    box[BOXTOP] = INT_MIN;
    box[BOXRIGHT] = INT_MIN;
    box[BOXBOTTOM] = INT_MAX;
    box[BOXLEFT] = INT_MAX;
}

void addtobox(float box[4], float x, float y)
{
    if (x < box[BOXLEFT])
	   box[BOXLEFT] = x;
    else if (x > box[BOXRIGHT])
	   box[BOXRIGHT] = x;
    if (y < box[BOXBOTTOM])
	   box[BOXBOTTOM] = y;
    else if (y > box[BOXTOP])
	   box[BOXTOP] = y;
}
