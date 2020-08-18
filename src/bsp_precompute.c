#include "../include/bsp.h"

static float cross_vertex(float x1 , float y1, float x2, float y2)
{
    return (x1 * y2 - y1 * x2);
}

static t_vecf2		intersect_vertex(t_vxinfo *vx, int nearside, int farside)
{
	float 	nearz;
	float 	farz;
    float   cross;
    t_vecf2 ret;

	nearz = 1e-4f;
	farz = 5.;
    ret.x = cross_vertex(vx->tx1, vx->tz1, vx->tx2, vx->tz2);
    ret.y = cross_vertex(nearside, nearz, farside, farz);
    cross = cross_vertex(vx->tx1 - vx->tx2, vx->tz1 - vx->tz2, nearside - farside,
        nearz - farz);
    ret.x = cross_vertex(ret.x, vx->tx1 - vx->tx2, ret.y, nearside - farside) / cross;
    ret.y = cross_vertex(ret.x, vx->tz1 - vx->tz2, ret.y, nearz - farz) / cross;
    return(ret);

}

static void		clip_vertex(t_vxinfo *vx)
{
	float 	nearside;
	float 	farside;
	t_vecf2 intersect1;
	t_vecf2	intersect2;

	nearside = 1e-5f;
	farside = 20.;
	intersect1 = intersect_vertex(vx, -nearside, -farside);
	intersect2 = intersect_vertex(vx, nearside, farside);
    if (vx->tz1 < 1e-4f)
    {
        vx->tx1 = (intersect1.y > 0) ? intersect1.x : intersect2.x;
        vx->tz1 = (intersect1.y > 0) ? intersect1.y : intersect2.y;
    }
    if (vx->tz2 < 1e-4f)
    {
        vx->tx2 = (intersect1.y > 0) ? intersect1.x : intersect2.x;
        vx->tz2 = (intersect1.y > 0) ? intersect1.y : intersect2.y;
    }
}

int		precompute_vertex(t_vxinfo *vx, t_line *line, t_player *pl)
{
	float 	pcos;
	float 	psin;

	psin = pl->cam.dvl_lr.dx;
	pcos = pl->cam.dvl_lr.dy;
	vx->vx1.x = line->p1.x - pl->x;
	vx->vx1.y = line->p1.y - pl->y;
	vx->vx2.x = line->p2.x - pl->x;
	vx->vx2.y = line->p2.y - pl->y;
	vx->tx1 = vx->vx1.x * psin - vx->vx1.y * pcos;
	vx->tx2 = vx->vx2.x * psin - vx->vx2.y * pcos;
	vx->tz1 = vx->vx1.x * pcos + vx->vx1.y * psin;
	vx->tz2 = vx->vx2.x * pcos + vx->vx2.y * psin;
	if (vx->tz1 > 0 && vx->tz2 > 0)
		return (ERROR);
	//normalement deja fait
	if (vx->tz1 <= 0 || vx->tz2 <= 0)
		clip_vertex(vx);
	return (SUCCESS);
}
