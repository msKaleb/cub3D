/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:23:06 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/05 16:19:13 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d_bonus.h"

void	init_raycast(t_raycast *ray, t_data *data)
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
	ray->ceiling_col = data->ceiling_col;
	ray->floor_col = data->floor_col;
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
	m.player.map = parser_bonus(argv[1], &data);
	if (!m.player.map)
		return (printf("Failed map loading\n"), 1);
	for(int i = 0; m.player.map[i]; i++)
	{
		printf("%s", m.player.map[i]);
	}
	printf("\n\nfinish write map to render\n");
	for(int i = 0; data.minimap[i]; i++)
	{
		printf("%s", data.minimap[i]);
	}
	printf("\n\nfinish write map to minimap\n");
	init_mlx(&m);
	init_raycast(&m.ray, &data);
	m.player.dir = data.dir_person;
	init_player(&m.player, &data, &m);
	raycast(&m.ray, &m.player, &m);
	// minimap(&m, &data);

	// mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
	mlx_hook(m.win, ON_KEYDOWN, (1L<<0), &set_motion, &m);
	mlx_hook(m.win, ON_KEYUP, (1L<<1), &release_motion, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx, &m);
	printf("Line: %d File: %s\n", __LINE__, __FILE__);
	mlx_loop_hook(m.mlx, &render_frame, &m);
	mlx_loop(m.mlx);
	printf("Line: %d File: %s\n", __LINE__, __FILE__);
	// free_2dimension(map);
	return(0);
}
