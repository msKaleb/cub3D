/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:23:06 by msoria-j          #+#    #+#             */
/*   Updated: 2023/12/31 18:07:16 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

// more testing :[
void	render_test(t_mlx *m)
{
	for (int i = DEFAULT_X / 3; i < DEFAULT_X - (DEFAULT_X / 3); i++)
		for (int j = DEFAULT_Y / 3; j < DEFAULT_Y - (DEFAULT_Y / 3); j++)
			print_pixel(m, (t_point){i,j}, DEFAULT_COLOR);
}

// to be put into another file, e.g. player.c
// change the values to the ones from the map
// now it's looking west
void	init_player(t_player *player)
{
	player->pos_x = 17.5;
	player->pos_y = 8.5;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = -0.66;
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
	// 1111111111111111111
	// 10W1001001001000001
	// 1011000001000001001
	// 1001001001111101111
	// 1001111000001001001
	// 1000000000000001001
	// 1001111111111001001
	// 1111000000000001011
	// 1000000001000000001
	// 1111111111111111111
	{
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
		(void)test_map;
		t_player	mikel;
		mikel.map = test_map;
		/* mikel.map = malloc(sizeof(char *) * 7);
		for (int i = 0; i < 7; i++)
			mikel.map[i] = ft_strdup(test_map[i]); */
		// printf("%c\n", mikel.map[5][7]);
		init_raycast(&ray);
		init_player(&mikel);
		raycast(&ray, &mikel, &m);
	}
	// testing....

	// render_test(&m);
	mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
	mlx_key_hook(m.win, &key_hook, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx, &m);
	mlx_loop(m.mlx);
	// free_2dimension(map);
	close(fd);
	return(0);
}
