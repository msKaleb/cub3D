/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:32:54 by nimai             #+#    #+#             */
/*   Updated: 2024/01/10 12:25:47 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d_bonus.h"
#include "colors.h"

static void	print_one_block(t_mlx *m, t_point point, int colour)
{
	t_point pos;

	pos.x = (point.x * m->player.data->blocksize);
	while (pos.x < ((point.x * m->player.data->blocksize) + m->player.data->blocksize))
	{
		pos.y = (point.y * m->player.data->blocksize);
		while (pos.y < ((point.y * m->player.data->blocksize) + m->player.data->blocksize))
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

void	minimap(t_mlx *m, t_data *data)
{
	// locate_player(m, data);
	data->pt_person.x = (int)round(m->player.pos_x * 2);
	data->pt_person.y = (int)round(m->player.pos_y * 2);
	// printf(GREEN "map_size.x: %d\n", data->map_size.x);
	// printf(GREEN "map_size.y: %d\n", data->map_size.y);
	if (data->map_size.x > 75 || data->map_size.y > 75)
		data->blocksize = 1;
	else if (data->map_size.x > 35 || data->map_size.y > 35)
		data->blocksize = 2;
	// printf("blocksize: %d%s\n", data->blocksize, RESET);
	draw_minimap(m, data);
}
