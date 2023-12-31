#include "ft_cub3d.h"

static void	set_ray_values(t_raycast *ray, t_player *player, int x)
{
	ray->cam_x = 2 * x / DEFAULT_X - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->cam_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->cam_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_x = fabs(1 / ray->dir_x); // zero division?
	ray->delta_y = fabs(1 / ray->dir_y);
	if (ray->dir_y == 0 || ray->dir_x == 0)
		printf("zero_division\n");
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

/* static void	set_dda(t_raycast *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (player->pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (player->pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_y;
	}
} */

/**
 * @brief performs DDA algorithm
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
		if (player->map[ray->map_y][ray->map_x] == '1') {
			ray->is_wall = 1;
			// printf("is wall [%d][%d]\n", ray->map_y, ray->map_x);
			// ray->side == 0 ? printf("side EW\n") : printf("side NS\n");
		} // map_y = rows, map_x = columns
		/* else
			printf("is NOT wall [%d][%d]\n", ray->map_y, ray->map_x); */
		// ray->is_wall = player->map[ray->map_y][ray->map_x] + '0';
	}
	ray->is_wall = 0;
}

static void	get_line_height(t_raycast *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_x - ray->delta_x;
	else
		ray->perp_wall_dist = ray->side_y - ray->delta_y;
	/* printf("wall_dist: %f | sidedist_x: %f | deltadist_x: %f\n", 
		ray->perp_wall_dist, ray->side_x, ray->delta_x); */
	ray->line_height = (int)(DEFAULT_Y / ray->perp_wall_dist);
	ray->line_first_px = DEFAULT_Y / 2 - ray->line_height / 2;
	// ray->line_first_px = -(ray->line_height) / 2 + DEFAULT_Y / 2;
	if (ray->line_first_px < 0)
		ray->line_first_px = 0;
	ray->line_last_px = DEFAULT_Y / 2 + ray->line_height / 2;
	// ray->line_last_px = ray->line_height / 2 + DEFAULT_Y / 2;
	if (ray->line_last_px > DEFAULT_Y)
		ray->line_last_px = DEFAULT_Y - 1;
}

/**
 * @brief cast a ray to "see" the worldd
 */
void	raycast(t_raycast *ray, t_player *player, t_mlx *m)
{
	int	x;
	(void)m;
	x = -1;
	while (++x < DEFAULT_X)
	{
		set_ray_values(ray, player, x);
		get_step_and_side(ray, player);
		// set_dda(ray, player);
		dda(ray, player);
		get_line_height(ray);
		print_line(ray, m, x);
		// write(1, ft_itoa(ray->perp_wall_dist), 1);
	}
}