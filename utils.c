/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:06:36 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/14 00:21:24 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	is_space(char c)
{
	if (c == ' ' || (c > 8 && c < 14))
		return (1);
	else
		return (0);
}

void	trim_non_ascii(char **tab, int rows)
{
	char	*tmp;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	k = 0;
	while (++i < rows)
	{
		tmp = ft_calloc(1, ft_strlen(tab[i]));
		while (++j < (int)ft_strlen(tab[i]))
		{
			if (!is_space(tab[i][j]))
				tmp[k++] = tab[i][j];
		}
		free(tab[i]);
		tab[i] = tmp;
		j = -1;
		k = 0;
	}
}

void	init_raycast(t_raycast *ray, t_data *data)
{
	ray->cam_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->delta_x = 0;
	ray->delta_y = 0;
	ray->side_x = 0;
	ray->side_y = 0;
	ray->perp_wall_dist = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->line_height = 0;
	ray->is_wall = 0;
	ray->side = 0;
	ray->ceiling_col = data->ceiling_col;
	ray->floor_col = data->floor_col;
}

void	free_map(t_player *player)
{
	int	i;
	int	rows;

	i = 0;
	rows = (int)player->height;
	while (i < rows)
	{
		free(player->map[i]);
		i++;
	}
	free(player->map);
}

t_dir	get_dir(char dir)
{
	if (dir == 'N')
		return ((t_dir){{0, -1, 1, 0}});
	else if (dir == 'S')
		return ((t_dir){{0, 1, -1, 0}});
	else if (dir == 'W')
		return ((t_dir){{-1, 0, 0, -1}});
	else if (dir == 'E')
		return ((t_dir){{1, 0, 0, 1}});
	else
		return ((t_dir){{0, -1, 1, 0}});
}
