/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:23:06 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/03 22:20:12 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	init_raycast(t_raycast *ray)
{
	ray->cam_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->delta_x = 0;
	ray->delta_y = 0;
	ray->side_x = 0;
	ray->side_y = 0;
	ray->perp_wall_dist = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->line_height = 0;
	ray->is_wall = 0;
	ray->side = 0;
	ray->ceiling_col = -1;
	ray->floor_col = -1;
}

int	test(int key_code, t_mlx *m)
{
	(void)m;
	printf("%d\n", key_code);
	return (0);
}
int	main(int argc, char *argv[])
{
	t_data		data;
	t_mlx		m;

	if (argc < 2)
		return (err_arg_number());
	if (check_file_format(argv[1]) == -1)
		return (err_arg_number());//error incorrect file format 
	init_mlx(&m);
	init_raycast(&m.ray);
	m.player.map = parser(argv[1], &data, &m.ray);
	if (!m.player.map)
		return (printf("Failed map loading\n"), 1);
	m.player.dir = data.dir_person;
	init_player(&m.player, &data, &m);
	raycast(&m.ray, &m.player, &m);

	// mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
	mlx_hook(m.win, ON_KEYDOWN, (1L<<0), &set_motion, &m);
	mlx_hook(m.win, ON_KEYUP, (1L<<1), &release_motion, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx, &m);
	mlx_loop_hook(m.mlx, &render_frame, &m);
	mlx_loop(m.mlx); 
	// free_2dimension(map);
	return(0);
}
