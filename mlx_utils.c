/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:37:30 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/14 10:45:46 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

/**
 * @brief free memory and destroy the mlx window
 * @note using MAX_TEXTURES for weapon free because uses the same amount
 * of images as textures array
 * @todo free minimap, but in mandatory there is no minimap. Avoid duplicating close_mlx
  */
int	close_mlx(t_mlx *m)
{
	int	i;

	i = -1;
	while (++i < MAX_TEXTURES)
	{
		if (m->player.text[i].texture)
			mlx_destroy_image(m->mlx, m->player.text[i].texture);
		if (m->player.weapon[i].img)
			mlx_destroy_image(m->mlx, m->player.weapon[i].img);
	}
	free_2dimension(m->player.map);
	free_data(m->player.data);
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
	int	i;
	
	i = -1;
	while (++i < MAX_TEXTURES)
	{
		m->player.text[i].texture = NULL;
		m->player.weapon[i].img = NULL;
	}
	m->mlx = NULL;
	m->win = NULL;
	m->img = NULL;
	m->mlx = mlx_init();
	if (m->mlx != NULL)
		m->win = mlx_new_window(m->mlx, DEFAULT_X, DEFAULT_Y, \
		"cub3D Project - nimai & msoria-j");
	if (m->win != NULL)
		m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	if (m->img == NULL)
		exit(err_mlx(m));
	m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->endian);
	m->cur.x = DEFAULT_X / 2;
	m->cur.y = DEFAULT_Y / 2;
	mlx_mouse_move(m->mlx, m->win, m->cur.x, m->cur.y);
	mlx_mouse_hide(m->mlx, m->win);
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
	return (0);
}
