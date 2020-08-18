#include "../include/bsp.h"

t_sector	    init_sector(float ceil, float floor)
{
	t_sector	sector;

    bzero(&sector, sizeof(t_sector));
    sector.ceil = ceil;
    sector.floor = floor;
	return (sector);
}
