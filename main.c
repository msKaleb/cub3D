/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:23:06 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/03 16:47:34 by nimai            ###   ########.fr       */
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
	// t_raycast	ray;
	int			fd = 0;
	// char		**map;

	// init_data(&data);
	if (argc < 2)
		return (err_arg_number());
	if (check_file_format(argv[1]) == -1)
		return (err_arg_number());//error incorrect file format 
	//
	//
	// fd = open(argv[1], O_RDONLY);
	// if (fd == -1)
	// 	return (err_file(argv[1]));
	//
	//
	/* parser */
	// map = parser(argv[1], &data);	
	// for (int i = 0; map[i]; i++)
	// 	printf("%s", map[i]);

	init_mlx(&m);
	// testing....
	// {
	// 	// 1111111111111111111
	// 	// 1001001001001000001
	// 	// 1011000001000001001
	// 	// 1001001001111101111
	// 	// 1001111000001001001
	// 	// 1000000000000001001
	// 	// 1001111111111001001
	// 	// 1111000000000001011
	// 	// 10000000010000000W1
	// 	// 1111111111111111111
	// 	// init on [8][17]
	// 	char	*test_map[10] = {
	// 		"1111111111111111111",
	// 		"1001001001001000001",
	// 		"1011000001000001001",
	// 		"1001001001111101111",
	// 		"1001111000001001001",
	// 		"1000000000000001001",
	// 		"1001111111111001001",
	// 		"1111000000000001011",
	// 		"1000000001000000001",
	// 		"1111111111111111111"
	// 	};
		// t_player	mikel;
	init_raycast(&m.ray);
	m.player.map = parser(argv[1], &data, &m.ray);
	m.player.dir = data.dir_person; // make it point westward, change to the character on the map
	init_player(&m.player, &data);
	raycast(&m.ray, &m.player, &m);
	// testing....

	close(fd);
	// mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
	mlx_hook(m.win, ON_KEYDOWN, (1L<<0), &set_motion, &m);
	mlx_hook(m.win, ON_KEYUP, (1L<<1), &release_motion, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx, &m);
	mlx_loop_hook(m.mlx, &render_frame, &m);
	mlx_loop(m.mlx); 
	// free_2dimension(map);
	return(0);
}
