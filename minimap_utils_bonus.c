/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:32:54 by nimai             #+#    #+#             */
/*   Updated: 2024/01/10 15:51:20 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d_bonus.h"
#include "colors.h"

static void	print_player(t_mlx *m, t_data *data, t_point point, t_point size)
{
	t_point	pos;
	t_point	start;

	pos.x = ((point.x + 1) * data->blocksize - size.x);
	if (!data->flag_mmap)
		pos.x += (DEFAULT_X / 2) - ((data->map_size.x * data->blocksize) / 2) - 1;
	start.x = pos.x;
	while (pos.x < (start.x + data->blocksize))
	{
		pos.y = ((point.y - data->pos_map + 1) * data->blocksize - size.y);
		if (!data->flag_mmap)
			pos.y += (DEFAULT_Y / 2) - ((data->map_size.y * data->blocksize) / 2) - 1;
		start.y = pos.y;
		while (pos.y < (start.y + data->blocksize))
		{
			// print_pixel(m, pos, 0x00000000);
			print_pixel(m, pos, 0x00FF8300);
			pos.y++;
		}
		pos.x++;
	}
}

static void	draw_player_side_edge(t_mlx *m, t_point i, t_data *data, t_point size)
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
	else if (data->minimap[i.y][i.x] == '0' && (data->minimap[i.y][i.x - 1] == '1' || data->minimap[i.y - 1][i.x] == '1' || data->minimap[i.y - 1][i.x - 1] == '1'))
		draw_player_side_edge(m, i, data, size);			
	else
		print_player(m, data, i, size);
}
