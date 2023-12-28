/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:23:06 by msoria-j          #+#    #+#             */
/*   Updated: 2023/12/28 19:05:05 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

char	**test_map(void)
{
	char	**map = (char *[]){
		"1111111111",
		"1000000011",
		"1000000001",
		"1101000001",
		"1100100001",
		"1110110N01",
		"1111111111",
	};
	return (map);
}

int	main(int argc, char *argv[])
{
	t_mlx	m;
	int		fd;
	t_data	data;
	char	**map;

	if (argc < 2)
		return (err_arg_number());
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (err_file(argv[1]));
	/* parser */
	// map = parser(argv[1], &data);	
	// for (int i = 0; map[i]; i++)
	// 	printf("%s", map[i]);
	/*  */
	init_mlx(&m);
	mlx_key_hook(m.win, &key_hook, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx, &m);
	mlx_loop(m.mlx);
	close(fd);
	return(0);
}
