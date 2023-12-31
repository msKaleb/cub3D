#include "ft_cub3d.h"

/*
*In order to know where to put the vertex, we calculate the offset
*using the values filled by the 'mlx_get_data_addr()' function:
*bits per pixel, size of line, and the endian value, then we use the formula
*'y * size_line + x * (bits_per_pixel / 8)' to change the atributes
*of a specific vertex (or pixel).
*/
void	print_pixel(t_mlx *m, t_point p, int color)
{
	char	*ptr;
	int		offset;

	if (p.x < 0 || p.y < 0)
		return ;
	if (p.x > DEFAULT_X || p.y > DEFAULT_Y)
		return ;
	offset = (p.y * m->sl) + (p.x * (m->bpp / 8));
	ptr = m->addr + offset;
	*(unsigned int *)ptr = mlx_get_color_value(m->mlx, color);
}

void	print_line(t_raycast *ray, t_mlx *m, int x)
{
	int	y;

	y = ray->line_first_px;
	while (y++ <= ray->line_last_px)
		print_pixel(m, (t_point){x, y}, DEFAULT_COLOR);
}
