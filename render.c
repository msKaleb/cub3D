#include "ft_cub3d.h"

void	print_texel(t_mlx *m, t_point p, int color)
{
	char	*ptr;
	int		offset;

	if (p.x < 0 || p.y < 0)
		return ;
	if (p.x > DEFAULT_X || p.y > DEFAULT_Y)
		return ;
	offset = (p.y * m->texture.size_line) + (p.x * (m->texture.bpp / 8));
	ptr = m->texture.text_addr + offset;
	*(unsigned int *)ptr = mlx_get_color_value(m->mlx, color);
}

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
	int	color;

	y = 0;
	color = DEFAULT_COLOR; // remove this
	if (ray->side == 1)
		color = color / 2;
	// print the ceiling
	while (y < ray->line_first_px)
		print_pixel(m, (t_point){x, y++}, ray->ceiling_col);
	// print the line (change this loop for color from get_texel_color)
	/* while (y < ray->line_last_px)
		print_pixel(m, (t_point){x, y++}, color); */
	get_texel_color(m, &m->player.text[0], x); // change [0] for needed one (NO SO EA WE)
	y += ray->line_height;
	// print_texture_line(first_px, last_px)
	// print the floor
	while (y < DEFAULT_Y)
		print_pixel(m, (t_point){x, y++}, ray->floor_col);
}
