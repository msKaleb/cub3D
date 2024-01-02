/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:37:30 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/02 18:54:25 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	close_mlx(t_mlx *m)
{
	// freemap(m->v);
	mlx_destroy_window(m->mlx, m->win);
	free(m->mlx);
	exit(EXIT_SUCCESS);
}

int	key_hook(int key_code, t_mlx *m)
{
	if (key_code == XK_ESCAPE)
		close_mlx(m);
	if (has_to_move(key_code))
	{
		mlx_destroy_image(m->mlx, m->img);
		m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
		move_player(m, key_code);
		rotate_player(m, key_code);
		raycast(&m->ray, &m->player, m);
		mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
	}
	return (0);
}

void	init_mlx(t_mlx *m)
{
	m->mlx = mlx_init();
	if (m->mlx == NULL)
		exit (err_mlx()); // leaks?
	m->win = mlx_new_window(m->mlx, DEFAULT_X, DEFAULT_Y, \
		"cub3D Project - nimai & msoria-j");
	if (m->win == NULL)
		exit(err_mlx()); // leaks?
	m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	if (m->img == NULL)
		exit(err_mlx()); // leaks?
	m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->endian);
}

void	render_frame()
{
	
}
