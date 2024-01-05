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


void	draw_minimap(t_mlx *m, t_data *data)
{
	t_point	i;

	i.x = -1;
	i.y = -1;

	(void)m;
	// (void)data;
	printf("let's draw!\n");
	while (++i.y < data->map_size.y)
	{
		while (++i.x < data->map_size.x)
		{
			if (data->minimap[i.y][i.x] == 32)
			{
				
			}
			if (data->minimap[i.y][i.x] == '1')
			{
				
			}
			if (data->minimap[i.y][i.x] == '0')
			{
				
			}
		}
	}

}


void	minimap(t_mlx *m, t_data *data)
{
	// (void)m;
	// (void)data;

	m->addr = (unsigned int *)mlx_get_data_addr(&m->img, &m->bpp, &m->sl, &m->endian);
	printf("m->addr: %p\n", m->addr);
	printf("&m->img: %p\n", &m->img);
	printf("&m->bpp: %p\n", &m->bpp);
	printf("&m->sl: %p\n", &m->sl);
	printf("&m->endian: %p\n", &m->endian);
	printf("&m->mlx: %p\n", &m->mlx);
	printf("&m->win: %p\n", &m->win);
	printf("&m->img: %p\n\n", &m->img);

	draw_minimap(m, data);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
	printf(GREEN "put minimap!%s\n", RESET);
}

