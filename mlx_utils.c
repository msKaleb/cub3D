/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:37:30 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/05 15:30:33 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	close_mlx(t_mlx *m)
{
	free_map(&m->player);
	mlx_destroy_window(m->mlx, m->win);
	free(m->mlx);
	exit(EXIT_SUCCESS);
}

/* int	key_hook(int key_code, t_mlx *m)
{
	if (key_code == XK_ESCAPE)
		close_mlx(m);
	if (has_to_move(key_code))
	{
		// mlx_destroy_image(m->mlx, m->img);
		// m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
		set_motion(key_code, m);
		// raycast(&m->ray, &m->player, m);
		// mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
	}
	return (0);
} */

/**
 * @todo check leaks on exit()
  */
void	init_mlx(t_mlx *m)
{
	m->mlx = mlx_init();
	if (m->mlx == NULL)
		exit (err_mlx());
	m->win = mlx_new_window(m->mlx, DEFAULT_X, DEFAULT_Y, \
		"cub3D Project - nimai & msoria-j");
	if (m->win == NULL)
		exit(err_mlx());
	m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	if (m->img == NULL)
		exit(err_mlx());
	m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->endian);
}

// char *ns = ft_itoa(m->player.motion_ns);
// char *ew = ft_itoa(m->player.motion_ew);
// mlx_string_put(m->mlx, m->win, 20, 20, 0x00FFFFFF, ns);
// mlx_string_put(m->mlx, m->win, 20, 40, 0x00FFFFFF, ew);
int	render_frame(t_mlx *m)
{
	move_player(m);
	rotate_player(m);
	mlx_destroy_image(m->mlx, m->img);
	m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	raycast(&m->ray, &m->player, m);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
	return (0);
}

int	set_motion(int key_code, t_mlx *m)
{
	if (key_code == XK_ESCAPE)
		close_mlx(m);
	if (key_code == XK_W)
		m->player.motion_ns = 1;
	else if (key_code == XK_S)
		m->player.motion_ns = -1;
	else if (key_code == XK_A)
		m->player.motion_ew = 1;
	else if (key_code == XK_D)
		m->player.motion_ew = -1;
	else if (key_code == XK_LEFT)
		m->player.motion_rot = -1;
	else if (key_code == XK_RIGHT)
		m->player.motion_rot = 1;
	render_frame(m);
	return (0);
}

int	release_motion(int key_code, t_mlx *m)
{
	if (key_code == XK_W)
		m->player.motion_ns = 0;
	else if (key_code == XK_S)
		m->player.motion_ns = -0;
	else if (key_code == XK_A)
		m->player.motion_ew = -0;
	else if (key_code == XK_D)
		m->player.motion_ew = 0;
	else if (key_code == XK_LEFT)
		m->player.motion_rot = -0;
	else if (key_code == XK_RIGHT)
		m->player.motion_rot = 0;
	return (0);
}
