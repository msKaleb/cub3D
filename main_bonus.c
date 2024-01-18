/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:23:06 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/18 17:08:21 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d_bonus.h"

int	mouse_hook(int button, int x, int y, t_mlx *m)
{
	(void)x;
	(void)y;
	if (button == 1)
		m->player.shot_flag = 1;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_mlx		m;

	if (argc < 2 || (check_file_format(argv[1]) == -1))
		return (err_arg_number());
	m.player.map = parser_bonus(argv[1], &data);
	if (!m.player.map)
	{
		free_data(&data);
		return (err_map());
	}
	init_mlx(&m);
	init_raycast(&m.ray, &data);
	init_player(&m.player, &data, &m);
	load_weapon(&m, &m.player.weapon[0]);
	raycast(&m.ray, &m.player, &m);
	mlx_mouse_hook(m.win, mouse_hook, &m);
	mlx_hook(m.win, ON_KEYDOWN, X_KEYPRESS, &set_motion_bonus, &m);
	mlx_hook(m.win, ON_KEYUP, X_KEYRELEASE, &release_motion_bonus, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx_bonus, &m);
	mlx_hook(m.win, ON_MOUSEMOVE, X_POINTERMOTION, &mouse_rotation_bonus, &m);
	mlx_loop_hook(m.mlx, &render_frame_bonus, &m);
	mlx_loop(m.mlx);
	return (0);
}
