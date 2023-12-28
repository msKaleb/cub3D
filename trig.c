#include "ft_cub3d.h"

int fix_ang(int a)
{
	if(a>359)
		a-=360;
	if(a<0)
		a+=360;
	return a;
}

float deg_to_rad(int a)
{
	return fix_ang(a) * M_PI / 180.0;
}