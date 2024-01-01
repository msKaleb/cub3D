/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:23:06 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/01 20:25:10 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

/**
 * @brief initialize the struct with parameters from the map
 * @note why do I have to add .5 to pos_x/y???
 * @todo change pos_x/y to the values on the map, now is for testing
  */
void	init_player(t_player *player)
{
	t_initial_dir	dir;

	if (player->dir == 'N')
		dir = (t_initial_dir){{0, -1, 1, 0}};
	else if (player->dir == 'S')
		dir = (t_initial_dir){{0, 1, -1, 0}};
	else if (player->dir == 'W')
		dir = (t_initial_dir){{-1, 0, 0, -1}};
	else if (player->dir == 'E')
		dir = (t_initial_dir){{1, 0, 0, 1}};
	player->pos_x = 17.5;
	player->pos_y = 8.5;
	player->dir_x = 0 + dir.orientation[0];
	player->dir_y = 0 + dir.orientation[1];
	player->plane_x = 0.66 * dir.orientation[2];
	player->plane_y = 0.66 * dir.orientation[3];
}

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
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_mlx		m;
	t_raycast	ray;
	int			fd;

	(void)data;

	if (argc < 2)
		return (err_arg_number());
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (err_file(argv[1]));
	/* parser */
	// map = parser(argv[1], &data);	
	// for (int i = 0; map[i]; i++)
	// 	printf("%s", map[i]);

	init_mlx(&m);
	// testing....
	{
		// 1111111111111111111
		// 1001001001001000001
		// 1011000001000001001
		// 1001001001111101111
		// 1001111000001001001
		// 1000000000000001001
		// 1001111111111001001
		// 1111000000000001011
		// 10000000010000000W1
		// 1111111111111111111
		// init on [1][2]
		char	*test_map[10] = {
			"1111111111111111111",
			"1001001001001000001",
			"1011000001000001001",
			"1001001001111101111",
			"1001111000001001001",
			"1000000000000001001",
			"1001111111111001001",
			"1111000000000001011",
			"1000000001000000001",
			"1111111111111111111"
		};
		t_player	mikel;
		mikel.map = test_map;
		init_raycast(&ray);
		mikel.dir = 'W'; // make it point westward, change to the character on the map
		init_player(&mikel);
		raycast(&ray, &mikel, &m);
	}
	// testing....

	mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
	mlx_key_hook(m.win, &key_hook, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx, &m);
	mlx_loop(m.mlx);
	// free_2dimension(map);
	close(fd);
	return(0);
}

