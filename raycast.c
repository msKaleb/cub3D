/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:47:09 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/09 14:25:06 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static void	set_ray_values(t_raycast *ray, t_player *player, int x)
{
	ray->cam_x = 2 * x / DEFAULT_X - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->cam_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->cam_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_x = fabs(1 / ray->dir_x);
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
 * @note side = 0 -> points west/eastwards (x axis)
 * @note side = 1 -> points south/northwards (y axis)
 */
static void	dda(t_raycast *ray, t_player *player)
{
	while (ray->is_wall == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y >= player->height || ray->map_x >= player->width
			|| ray->map_y < 0 || ray->map_x < 0)
			break ;
		if (player->map[ray->map_y][ray->map_x] == '1')
			ray->is_wall = 1;
	}
	ray->is_wall = 0;
}

/**
 * @brief since we are printing screen_width lines (e.g. 480),
 * we need to get how long is each wall
  */
static void	get_line_height(t_raycast *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_x - ray->delta_x;
	else
		ray->perp_wall_dist = ray->side_y - ray->delta_y;
	ray->line_height = (int)(DEFAULT_Y / ray->perp_wall_dist);
	ray->line_first_px = DEFAULT_Y / 2 - ray->line_height / 2;
	if (ray->line_first_px < 0 || ray->line_first_px > DEFAULT_Y)
		ray->line_first_px = 0;
	ray->line_last_px = DEFAULT_Y / 2 + ray->line_height / 2;
	if (ray->line_last_px > DEFAULT_Y || ray->line_last_px < 0)
		ray->line_last_px = DEFAULT_Y;
}

/**
 * @brief cast a ray to "see" the worldd
 */
void	raycast(t_raycast *ray, t_player *player, t_mlx *m)
{
	int	x;

	x = -1;
	while (++x < DEFAULT_X)
	{
		set_ray_values(ray, player, x);
		get_step_and_side(ray, player);
		dda(ray, player);
		get_line_height(ray);
		print_line(ray, m, x);
	}
}
