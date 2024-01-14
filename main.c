/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:23:06 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/14 17:31:02 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	main(int argc, char *argv[])
{
	t_data		data;
	t_mlx		m;

	if (argc < 2)
		return (err_arg_number());
	if (check_file_format(argv[1]) == -1)
		return (err_arg_number());
	m.player.map = parser(argv[1], &data);
	if (!m.player.map)
	{
		free_data(&data);
		return (err_map());
	}
	init_mlx(&m);
	init_raycast(&m.ray, &data);
	init_player(&m.player, &data, &m);
	raycast(&m.ray, &m.player, &m);
	mlx_hook(m.win, ON_KEYDOWN, X_KEYPRESS, &set_motion, &m);
	mlx_hook(m.win, ON_KEYUP, X_KEYRELEASE, &release_motion, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx, &m);
	mlx_loop_hook(m.mlx, &render_frame, &m);
	mlx_loop(m.mlx);
	return (0);
}
