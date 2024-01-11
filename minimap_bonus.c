/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:32:54 by nimai             #+#    #+#             */
/*   Updated: 2024/01/10 15:51:12 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d_bonus.h"
#include "colors.h"

int	transparant_colour(int colour)
{
	if (colour == 0x00FFFFFF)
		return (0x60FFFFFF);
	if (colour == 0x00000000)
		return (0x60000000);
	return (-1);
}

static void	print_one_block(t_mlx *m, t_data *data, t_point point, int colour)
{
	t_point	pos;
	t_point	start;

	// printf("Line: %d: colour: %d\n", __LINE__, colour);
	if (!data->flag_mmap)
		colour = transparant_colour(colour);
	// printf("Line: %d: colour: %d\n", __LINE__, colour);

	pos.x = ((point.x + 1) * data->blocksize);
	if (!data->flag_mmap)
		pos.x += (DEFAULT_X / 2) - ((data->map_size.x * data->blocksize) / 2) - 1;
	start.x = pos.x;
	while (pos.x < (start.x + data->blocksize))
	{
		pos.y = ((point.y - data->pos_map + 1) * m->player.data->blocksize);
		if (!data->flag_mmap)
			pos.y += (DEFAULT_Y / 2) - ((data->map_size.y * data->blocksize) / 2) - 1;
		start.y = pos.y;
		while (pos.y < (start.y + data->blocksize))
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

	i.y = data->pos_map;
	while (i.y < data->map_size.y + data->pos_map)
	{
		i.x = 0;
		while (data->minimap[i.y][i.x] && i.x < data->map_size.x)
		{
			if (data->minimap[i.y][i.x] == 'E' || \
			data->minimap[i.y][i.x] == 'S' || \
			data->minimap[i.y][i.x] == 'N' || \
			data->minimap[i.y][i.x] == 'W')
				print_one_block(m, data, i, 0x00FFFFFF);
			else if (data->minimap[i.y][i.x] == '1')
				print_one_block(m, data, i, 0x00000000);
			else if (data->minimap[i.y][i.x] == '0')
				print_one_block(m, data, i, 0x00FFFFFF);
			if (i.y == (data->pt_person.y) && i.x == (data->pt_person.x))
				draw_player(m, i, data);
			i.x++;
		}
		i.y++;
	}
}

void	minimap(t_mlx *m, t_data *data)
{
	//for now switch the map munual
	data->flag_mmap = 1;
	// locate_player(m, data);
	data->pt_person.x = (int)round(m->player.pos_x * 2);
	data->pt_person.y = (int)round(m->player.pos_y * 2);
	// printf(GREEN "map_size.x: %d\n", data->map_size.x);
	// printf(GREEN "map_size.y: %d\n", data->map_size.y);

	if (data->flag_mmap)
		data->blocksize = 250 / data->map_size.x;
	else
		data->blocksize = (DEFAULT_X / 2) / data->map_size.x;
	draw_minimap(m, data);
}
