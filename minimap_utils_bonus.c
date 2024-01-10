/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:32:54 by nimai             #+#    #+#             */
/*   Updated: 2024/01/10 10:58:38 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d_bonus.h"
#include "colors.h"

static void	print_player(t_mlx *m, t_point point, int colour, t_point size)
{
	t_point pos;

	pos.x = (point.x * m->player.data->blocksize - size.x);
	while (pos.x < ((point.x * m->player.data->blocksize) + m->player.data->blocksize))
	{
		pos.y = (point.y * m->player.data->blocksize - size.y);
		while (pos.y < ((point.y * m->player.data->blocksize) + m->player.data->blocksize))
		{
			print_pixel(m, pos, colour);
			pos.y++;
		}
		pos.x++;
	}
}

static void	draw_player_side_edge(t_mlx *m, t_point i, char **minimap, t_point size)
{
	if (minimap[i.y - 1][i.x - 1] == '1')
	{
		size.x = 0;
		size.y = 0;
	}
	else if (minimap[i.y][i.x - 1] == '1')
		size.x = 0;
	else if(minimap[i.y - 1][i.x] == '1')
		size.y = 0;
	print_player(m, i, 0x0000FFFF, size);
}

static void	draw_player_on_edge(t_mlx *m, t_point i, char **minimap, t_point size)
{
	size.x = 0;
	size.y = 0;
	if (minimap[i.y - 1][i.x - 1] != '1')
	{
		i.x -= 1;
		i.y -= 1;
	}
	else if (minimap[i.y][i.x - 1] == '1')
		i.y -= 1;
	else if (minimap[i.y - 1][i.x] == '1')
		i.x -= 1;
	print_player(m, i, 0x0000FFFF, size);
}

void	draw_player(t_mlx *m, t_point i, char **minimap)
{
	t_point	size;

	size.x = 1;
	size.y = 1;
	if (minimap[i.y][i.x] == '1')
		draw_player_on_edge(m, i, minimap, size);
	else if (minimap[i.y][i.x] == '0' && (minimap[i.y][i.x - 1] == '1' || minimap[i.y - 1][i.x] == '1' || minimap[i.y - 1][i.x - 1] == '1'))
		draw_player_side_edge(m, i, minimap, size);			
	else
		print_player(m, i, 0x0000FFFF, size);
}
