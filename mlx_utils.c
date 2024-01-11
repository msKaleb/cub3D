/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:37:30 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/11 13:23:00 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

/**
 * @brief free memory and destroy the mlx window
  */
int	close_mlx(t_mlx *m)
{
	free_map(&m->player);
	if (m->mlx && m->img)
		mlx_destroy_image(m->mlx, m->img);
	if (m->win)
		mlx_destroy_window(m->mlx, m->win);
	free(m->mlx);
	exit(EXIT_SUCCESS);
}

/**
 * @brief initializes the mlx instance, 
 * firstly to NULL to avoid potential double frees
  */
void	init_mlx(t_mlx *m)
{
	m->mlx = NULL;
	m->win = NULL;
	m->img = NULL;
	m->mlx = mlx_init();
	if (m->mlx == NULL)
		exit (err_mlx(m));
	m->win = mlx_new_window(m->mlx, DEFAULT_X, DEFAULT_Y, \
		"cub3D Project - nimai & msoria-j");
	if (m->win == NULL)
		exit(err_mlx(m));
	m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	if (m->img == NULL)
		exit(err_mlx(m));
	m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->endian);
}

/**
 * @brief set of events on key press
  */
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

/**
 * @brief set of events on key release
  */
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
	// else if (key_code == XK_SPACE)
	// 	if (get_type(m) == 2)
	// 		ft_fprintf(1, "Door!\n");	
	return (0);
}
