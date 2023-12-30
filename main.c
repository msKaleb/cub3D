/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:23:06 by msoria-j          #+#    #+#             */
/*   Updated: 2023/12/30 08:53:16 by msoria-j         ###   ########.fr       */
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
void	init_player(t_player *player)
{
	player->pos_x = 7;
	player->pos_y = 5;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
}

int	main(int argc, char *argv[])
{
	t_mlx	m;
	int		fd;
	t_data	data;

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

	// testing....
	{
		// init on [7][5]
		char	*test_map[7] = {
			"1111111111",
			"1000000011",
			"1000000001",
			"1101000001",
			"1100100001",
			"1110110001",
			"1111111111",
		};
		(void)test_map;
		t_player	mikel;
		
		init_player(&mikel);
		
	}
	// testing....

	init_mlx(&m);
	render_test(&m);
	mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
	mlx_key_hook(m.win, &key_hook, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx, &m);
	mlx_loop(m.mlx);
	// free_2dimension(map);
	close(fd);
	return(0);
}
