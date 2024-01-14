/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 00:13:44 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/14 17:36:23 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d_bonus.h"



char	*get_type(t_mlx *m)
{
	double	testx;
	double	testy;
	char	*c;

	testx = m->player.pos_x + m->player.dir_x
		* (MOVE_SPEED * 10);
	testy = m->player.pos_y + m->player.dir_y
		* (MOVE_SPEED * 10);
	c = &m->player.map[(int)testy][(int)testx];
	return (c);
}

/**
 * @brief calculates the next position of the player
 * and checks if it's inside a wall (collisions)
  */
void	move_player_bonus(t_mlx *m)
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
	if (ft_strchr("FD", m->player.map[(int)next_y][(int)next_x]))
	{
		m->player.pos_x = next_x;
		m->player.pos_y = next_y;
	}
}

/**
 * @brief initialize the struct with parameters from the map
 * @note add .5 to the position to place it in the center of the tile
  */
void	init_player_bonus(t_player *player, t_data *data, t_mlx *m)
{
	t_dir	dir;

	dir = get_dir(player->dir);
	player->pos_x = (double)data->pt_person.x + 0.5;
	player->pos_y = (double)data->pt_person.y + 0.5;
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
	// player->height = count_rows(player->map);
	player->data = data;
	m->player.dir = data->dir_person;
	load_textures_bonus(player->text, m, data);
}

/**
 * @brief rotates the camera in y axis with the mouse
 * @note MAC version
  */
/* int	mouse_rotation_bonus(int x, int y, t_mlx *m)
{
	if (x < 0)
		mlx_mouse_move(m->win, DEFAULT_X, y);
	else if (x > DEFAULT_X)
		mlx_mouse_move(m->win, 0, y);
	if (m->cur.x > x + 2)
		m->player.motion_rot = -1;
	else if (m->cur.x < x - 2)
		m->player.motion_rot = 1;
	else
		m->player.motion_rot = 0;
	m->cur.x = x;
	m->cur.y = y;
	return (0);
} */

/**
 * @brief rotates the camera in y axis with the mouse
 * @note Linux version
  */
int	mouse_rotation_bonus(int x, int y, t_mlx *m)
{
	if (x < 10)
		mlx_mouse_move(m->mlx, m->win, DEFAULT_X - 11, y);
	else if (x > DEFAULT_X - 10)
		mlx_mouse_move(m->mlx, m->win, 11, y);
	if (m->cur.x > x + 2)
		m->player.motion_rot = -1;
	else if (m->cur.x < x - 2)
		m->player.motion_rot = 1;
	else
		m->player.motion_rot = 0;
	m->cur.x = x;
	m->cur.y = y;
	return (0);
}
