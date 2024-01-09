/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:32:54 by nimai             #+#    #+#             */
/*   Updated: 2024/01/05 16:48:37 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d_bonus.h"
#include "colors.h"

// /*static*/ void	draw_player_edge(t_mlx *m, t_point i, char **minimap, t_point size)
// {
// 	if(minimap[i.y][i.x] == '0')
// 	{
// 		if (minimap[i.y - 1][i.x - 1] == '1')
// 		{
// 			size.x = 0;
// 			size.y = 0;
// 		}
// 		else if (minimap[i.y][i.x - 1] == '1')
// 			size.x = 0;
// 		else if(minimap[i.y - 1][i.x] == '1')
// 			size.y = 0;
// 	}
// 	else if (minimap[i.y][i.x] == '1')
// 	{
// 		size.x = 0;
// 		size.y = 0;
// 		if (minimap[i.y - 1][i.x - 1] != '1')
// 		{
// 			i.x -= 1;
// 			i.y -= 1;
// 		}
// 		else if (minimap[i.y][i.x - 1] == '1')
// 			i.y -= 1;
// 		else if (minimap[i.y - 1][i.x] == '1')
// 			i.x -= 1;
// 	}
// 	print_player(m, i, 0x0000FFFF, size);
// }

static void	print_one_block(t_mlx *m, t_point point, int colour)
{
	t_point pos;

	pos.x = (point.x * BLOCKSIZE);
	while (pos.x < ((point.x * BLOCKSIZE) + BLOCKSIZE))
	{
		pos.y = (point.y * BLOCKSIZE);
		while (pos.y < ((point.y * BLOCKSIZE) + BLOCKSIZE))
		{
			print_pixel(m, pos, colour);
			pos.y++;
		}
		pos.x++;
	}
}

static void	draw_minimap(t_mlx *m, t_data *data)
{
	t_point	i;

	i.y = 0;
	while (i.y < data->map_size.y * 2)
	{
		i.x = 0;
		while (data->minimap[i.y][i.x] && i.x < data->map_size.x * 2)
		{
			if (data->minimap[i.y][i.x] == 'E' || \
			data->minimap[i.y][i.x] == 'S' || \
			data->minimap[i.y][i.x] == 'N' || \
			data->minimap[i.y][i.x] == 'W')
				print_one_block(m, i, 0x00FFFFFF);
			else if (data->minimap[i.y][i.x] == '1')
				print_one_block(m, i, 0x00000000);
			else if (data->minimap[i.y][i.x] == '0')
				print_one_block(m, i, 0x00FFFFFF);				
			if (i.y == (data->pt_person.y) && i.x == (data->pt_person.x))
				draw_player(m, i, data->minimap);
			i.x++;
		}
		i.y++;
	}
}

// static void	locate_player(t_mlx *m, t_data *data)
// {
// 	data->pt_person.x = (int)round(m->player.pos_x * 2);
// 	data->pt_person.y = (int)round(m->player.pos_y * 2);
// 	printf(GREEN "data->pt_person.x: %d : data->pt_person.y: %d%s\n", data->pt_person.x, data->pt_person.y, RESET);
// }

void	minimap(t_mlx *m, t_data *data)
{
	// locate_player(m, data);
	data->pt_person.x = (int)round(m->player.pos_x * 2);
	data->pt_person.y = (int)round(m->player.pos_y * 2);
	draw_minimap(m, data);
}
