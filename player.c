/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:59:45 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/18 17:14:28 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static void	init_textures(t_player *player)
{
	int	i;

	i = -1;
	while (++i < MAX_TEXTURES)
	{
		player->text[i].texture = NULL;
		player->weapon[i].img = NULL;
	}
}

static int	count_rows(char **map)
{
	int	i;
	int	flag;
	int	rows;

	i = 0;
	rows = 0;
	flag = 0;
	while (map[i])
	{
		if (ft_strchr("1F0", map[i][0]))
			flag = 1;
		if (ft_strcmp(map[i], "\n") != 0 || flag == 0)
			rows++;
		i++;
	}
	return ((double)rows);
}

/**
 * @brief initialize the struct with parameters from the map
 * @note add .5 to the position to place it in the center of the tile
  */
void	init_player(t_player *player, t_data *data, t_mlx *m)
{
	t_dir	dir;

	init_textures(&m->player);
	player->dir = data->dir_person;
	player->pos_x = (double)data->pt_person.x + 0.5;
	player->pos_y = (double)data->pt_person.y + 0.5;
	dir = get_dir(player->dir);
	player->dir_x = 0 + dir.orientation[0];
	player->dir_y = 0 + dir.orientation[1];
	player->plane_x = 0.66 * dir.orientation[2];
	player->plane_y = 0.66 * dir.orientation[3];
	player->motion_ns = 0;
	player->motion_ew = 0;
	player->motion_rot = 0;
	player->wframe = 0;
	player->shot_flag = 0;
	player->width = (double)data->map_size.x;
	player->height = (double)data->map_size.y;
	player->height = count_rows(player->map);
	player->data = data;
	load_textures(player->text, m, data);
}

void	move_player(t_mlx *m)
{
	double	next_x;
	double	next_y;

	next_x = m->player.pos_x;
	next_y = m->player.pos_y;
	if (m->player.motion_ns != 0)
	{
		next_x = m->player.pos_x + m->player.dir_x
			* (MOVE_SPEED * m->player.motion_ns);
		next_y = m->player.pos_y + m->player.dir_y
			* (MOVE_SPEED * m->player.motion_ns);
	}
	if (m->player.motion_ew != 0)
	{
		next_x = m->player.pos_x + m->player.dir_y
			* (MOVE_SPEED * m->player.motion_ew / 2);
		next_y = m->player.pos_y + m->player.dir_x
			* (MOVE_SPEED * -m->player.motion_ew / 2);
	}
	if ((next_x >= 0 && next_y >= 0)
		&& (next_x <= m->player.width + 1 && next_y <= m->player.height + 1))
	{
		m->player.pos_x = next_x;
		m->player.pos_y = next_y;
	}
}

// rotation matrix:
// [ cos(a) -sin(a) ]
// [ sin(a)  cos(a) ]
void	rotate_player(t_mlx *m)
{
	double	dir_x;
	double	plane_x;

	dir_x = m->player.dir_x;
	plane_x = m->player.plane_x;
	if (m->player.motion_rot != 0)
	{
		m->player.dir_x = dir_x * cos(ROTATION_SPEED * m->player.motion_rot)
			- m->player.dir_y * sin(ROTATION_SPEED * m->player.motion_rot);
		m->player.dir_y = dir_x * sin(ROTATION_SPEED * m->player.motion_rot)
			+ m->player.dir_y * cos(ROTATION_SPEED * m->player.motion_rot);
		m->player.plane_x = plane_x * cos(ROTATION_SPEED * m->player.motion_rot)
			- m->player.plane_y * sin(ROTATION_SPEED * m->player.motion_rot);
		m->player.plane_y = plane_x * sin(ROTATION_SPEED * m->player.motion_rot)
			+ m->player.plane_y * cos(ROTATION_SPEED * m->player.motion_rot);
	}
}
