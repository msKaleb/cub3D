/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:23:06 by msoria-j          #+#    #+#             */
/*   Updated: 2023/12/28 18:25:36 by msoria-j         ###   ########.fr       */
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

	if (argc < 2)
		return (err_arg_number());
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (err_file(argv[1]));
	init_mlx(&m);
	mlx_key_hook(m.win, &key_hook, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx, &m);
	mlx_loop(m.mlx);
	close(fd);
	return(0);
}
