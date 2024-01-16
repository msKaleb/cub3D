/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:59:44 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/16 13:59:45 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d_bonus.h"

/**
 * @brief free memory and destroy the mlx window
 * @note using MAX_TEXTURES for weapon free because uses the same amount
 * of images as textures array
  */
int	close_mlx_bonus(t_mlx *m)
{
	free_2dimension(m->player.map);
	free_2dimension(m->player.data->minimap);
	free_data(m->player.data);
	if (m->mlx && m->img)
		mlx_destroy_image(m->mlx, m->img);
	if (m->win)
		mlx_destroy_window(m->mlx, m->win);
	free(m->mlx);
	exit(EXIT_SUCCESS);
}
