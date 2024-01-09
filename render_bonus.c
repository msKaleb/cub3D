#include "ft_cub3d_bonus.h"

/**
* @brief In order to know where to put the vertex, we calculate the offset
* using the values filled by the 'mlx_get_data_addr()' function:
* bits per pixel, size of line, and the endian value, then we use the formula
* '(y * size_line) + (x * (bits_per_pixel / 8))' to change the atributes
* of a specific pixel.
 */
// void	print_pixel(t_mlx *m, t_point p, int color)
// {
// 	char	*ptr;
// 	int		offset;

// 	if (p.x < 0 || p.y < 0)
// 		return ;
// 	if (p.x > DEFAULT_X || p.y > DEFAULT_Y)
// 		return ;
// 	offset = (p.y * m->sl) + (p.x * (m->bpp / 8));
// 	ptr = m->addr + offset;
// 	*(unsigned int *)ptr = mlx_get_color_value(m->mlx, color);
// }

/**
 * @brief for each x coordinate, prints the corresponding line,
 * starting with the ceiling (first loop), next the portion
 * corresponding to the wall (print_wall_line()), and finally a
 * loop for the floor portion
  */
// void	print_line(t_raycast *ray, t_mlx *m, int x)
// {
// 	int	y;

// 	y = 0;
// 	while (y < ray->line_first_px)
// 		print_pixel(m, (t_point){x, y++}, ray->ceiling_col);
// 	print_wall_line(m, m->player.text, x);
// 	y += ray->line_height;
// 	while (y < DEFAULT_Y)
// 		print_pixel(m, (t_point){x, y++}, ray->floor_col);
// }

// char *ns = ft_itoa(m->player.motion_ns);
// char *ew = ft_itoa(m->player.motion_ew);
// mlx_string_put(m->mlx, m->win, 20, 20, 0x00FFFFFF, ns);
// mlx_string_put(m->mlx, m->win, 20, 40, 0x00FFFFFF, ew);




/**
 * @brief refreshes the frame and applies character movement
  */
int	render_frame_bonus(t_mlx *m)
{
	move_player_bonus(m);
	rotate_player(m);
	mlx_destroy_image(m->mlx, m->img);
	m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	raycast(&m->ray, &m->player, m);
	minimap(m, m->player.data);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
	return (0);
}
