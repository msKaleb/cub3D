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

static void	set_ray_values(t_raycast *ray, t_player *player, int x)
{
	ray->cam_x = 2 * x / DEFAULT_X - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->cam_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->cam_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_x = fabs(1 / ray->dir_x); // zero division?
	ray->delta_y = fabs(1 / ray->dir_y);
}

/**
 * @brief calculate step and initial side distance
 */
static void	get_step_and_side(t_raycast *ray, t_player *player)
{
	if (ray->dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
	if (ray->step_x < 0)
		ray->side_x = (player->pos_x - ray->map_x) * ray->delta_x;
	else
		ray->side_x = (ray->map_x + 1 - player->pos_x) * ray->delta_x;
	if (ray->step_y < 0)
		ray->side_y = (player->pos_y - ray->map_y) * ray->delta_y;
	else
		ray->side_y = (ray->map_y + 1 - player->pos_y) * ray->delta_y;
}

/**
 * @brief performs DDA algorithm
 */
static void	dda(t_raycast *ray, t_player *player)
{
	while (ray->is_wall == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->step_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->step_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		/* if (player->map[ray->map_y][ray->map_x] == '1') // map_y = rows, map_x = columns
			ray->is_wall = 1; */
		ray->is_wall = player->map[ray->map_y][ray->map_x] + '0';
		// check some values
		printf("%d", ray->is_wall);
	}
	ray->is_wall = 0;
}

/**
 * @brief cast a ray to "see" the worldd
 */
void	raycast(t_raycast *ray, t_player *player/* , t_mlx *m */)
{
	int	x;

	x = 0;
	while (x++ < DEFAULT_X)
	{
		set_ray_values(ray, player, x);
		get_step_and_side(ray, player);
		dda(ray, player);
		if (ray->side == 0)
			ray->perp_wall_dist = ray->side_x - ray->delta_x;
		else
			ray->perp_wall_dist = ray->side_y - ray->delta_y;

	}
}
