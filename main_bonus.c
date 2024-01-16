/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:23:06 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/16 13:59:31 by msoria-j         ###   ########.fr       */
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

/**
 * @note previous version
  */
/* int	main(int argc, char *argv[])
{
	t_data		data;
	t_mlx		m;

	if (argc < 2)
		return (err_arg_number());
	if (check_file_format(argv[1]) == -1)
		return (err_arg_number());//error incorrect file format 
	m.player.map = parser_bonus(argv[1], &data);
	if (!m.player.map)
	{
		free_data(&data);
		return (printf("Failed map loading\n"), 1);
	}
	init_mlx(&m);
	m.cur.x = DEFAULT_X / 2;
	m.cur.y = DEFAULT_Y / 2;
	mlx_mouse_move(m.win, DEFAULT_X / 2, DEFAULT_Y / 2); // MAC version
	// mlx_mouse_move(m.mlx, m.win,
		DEFAULT_X / 2, DEFAULT_Y / 2); // Linux version
	mlx_mouse_hide(m.mlx, m.win);
	// printf("Line: %d / %s\n", __LINE__, __FILE__);
	init_raycast(&m.ray, &data);
	m.player.dir = data.dir_person;
	init_player(&m.player, &data, &m);
	load_weapon(&m, &m.player.weapon[0]);
	// printf("Line: %d / %s\n", __LINE__, __FILE__);
	raycast(&m.ray, &m.player, &m);
	// mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
	mlx_mouse_hook(m.win, mouse_hook, &m);
	mlx_hook(m.win, ON_KEYDOWN, X_KEYPRESS, &set_motion_bonus, &m);
	mlx_hook(m.win, ON_KEYUP, X_KEYRELEASE, &release_motion_bonus, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx, &m);
	mlx_hook(m.win, ON_MOUSEMOVE, X_POINTERMOTION, &mouse_rotation_bonus, &m);

	mlx_loop_hook(m.mlx, &render_frame_bonus, &m);
	mlx_loop(m.mlx);
	free_2dimension(m.player.map);
	free_2dimension(data.minimap);
	free_data(&data);
	return(0);
} */
