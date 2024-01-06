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

void	draw_one_block(t_mlx *m, t_point point, int colour)
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

void	draw_minimap(t_mlx *m, t_data *data)
{
	t_point	i;

	i.y = -1;

	// (void)m;
	// (void)data;
	printf("let's draw!\n");
	printf("data->map_size.y: %d\n", data->map_size.y);
	printf("data->map_size.x: %d\n", data->map_size.x);
	while (++i.y < data->map_size.y)
	{
		i.x = -1;
		while (++i.x < data->map_size.x)
		{
			if (data->minimap[i.y][i.x] == 32)
			{
				draw_one_block(m, i, 0x00FFFFFF);
			}
			else if (data->minimap[i.y][i.x] == '1')
			{
				draw_one_block(m, i, 0x00000000);
			}
			else if (data->minimap[i.y][i.x] == '0')
			{
				draw_one_block(m, i, 0x00FF0000);				
			}
		}
	}

}


void	minimap(t_mlx *m, t_data *data)
{
	// (void)m;
	// (void)data;

	// m->addr = (unsigned int *)mlx_get_data_addr(&m->img, &m->bpp, &m->sl, &m->endian);
	printf("m->addr: %p\n", m->addr);
	printf("&m->img: %p\n", &m->img);
	printf("&m->bpp: %p\n", &m->bpp);
	printf("&m->sl: %p\n", &m->sl);
	printf("&m->endian: %p\n", &m->endian);
	printf("&m->mlx: %p\n", &m->mlx);
	printf("&m->win: %p\n", &m->win);
	printf("&m->img: %p\n\n", &m->img);

	draw_minimap(m, data);
	// mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
	printf(GREEN "put minimap!%s\n", RESET);
}

