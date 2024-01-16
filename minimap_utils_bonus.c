/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:32:54 by nimai             #+#    #+#             */
/*   Updated: 2024/01/16 13:33:16 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d_bonus.h"

static void	print_player(t_mlx *m, t_data *data, t_point point, t_point size)
{
	t_point	pos;
	t_point	start;

	pos.x = ((point.x + 1) * data->blocksize - size.x);
	start.x = pos.x;
	while (pos.x < (start.x + data->blocksize))
	{
		pos.y = ((point.y - data->pos_map + 1) * data->blocksize - size.y);
		start.y = pos.y;
		while (pos.y < (start.y + data->blocksize))
		{
			print_pixel(m, pos, 0x00FF8300);
			pos.y++;
		}
		pos.x++;
	}
}

static void	draw_player_side_edge(t_mlx *m, t_point i, \
t_data *data, t_point size)
{
	if (data->minimap[i.y - 1][i.x - 1] == '1')
	{
		size.x = 0;
		size.y = 0;
	}
	else if (data->minimap[i.y][i.x - 1] == '1')
		size.x = 0;
	else if (data->minimap[i.y - 1][i.x] == '1')
		size.y = 0;
	print_player(m, data, i, size);
}

static void	draw_player_on_edge(t_mlx *m, t_point i, t_data *data, t_point size)
{
	size.x = 0;
	size.y = 0;
	if (data->minimap[i.y - 1][i.x - 1] != '1')
	{
		i.x -= 1;
		i.y -= 1;
	}
	else if (data->minimap[i.y][i.x - 1] == '1')
		i.y -= 1;
	else if (data->minimap[i.y - 1][i.x] == '1')
		i.x -= 1;
	print_player(m, data, i, size);
}

void	draw_player(t_mlx *m, t_point i, t_data *data)
{
	t_point	size;

	size.x = 1;
	size.y = 1;
	if (data->minimap[i.y][i.x] == '1')
		draw_player_on_edge(m, i, data, size);
	else if (data->minimap[i.y][i.x] == '0' && \
	(data->minimap[i.y][i.x - 1] == '1' || data->minimap[i.y - 1][i.x] == '1' \
	|| data->minimap[i.y - 1][i.x - 1] == '1'))
		draw_player_side_edge(m, i, data, size);
	else
		print_player(m, data, i, size);
}
