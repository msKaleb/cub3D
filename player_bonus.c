/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 00:13:44 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/16 12:58:31 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d_bonus.h"

/**
 * @brief set of events on key press
  */
int	set_motion_bonus(int key_code, t_mlx *m)
{
	if (key_code == XK_ESCAPE)
		close_mlx(m);
	if (key_code == XK_W)
		m->player.motion_ns = 1;
	else if (key_code == XK_S)
		m->player.motion_ns = -1;
	else if (key_code == XK_A)
		m->player.motion_ew = 1;
	else if (key_code == XK_D)
		m->player.motion_ew = -1;
	else if (key_code == XK_LEFT)
		m->player.motion_rot = -1;
	else if (key_code == XK_RIGHT)
		m->player.motion_rot = 1;
	else if (key_code == XK_UP)
		m->player.shot_flag = 1;
	render_frame_bonus(m);
	return (0);
}

/**
 * @brief set of events on key release
  */
int	release_motion_bonus(int key_code, t_mlx *m)
{
	char	*current;
	char	*to_check;

	current = &m->player.map[(int)m->player.pos_y][(int)m->player.pos_x];
	if (key_code == XK_W)
		m->player.motion_ns = 0;
	else if (key_code == XK_S)
		m->player.motion_ns = 0;
	else if (key_code == XK_A)
		m->player.motion_ew = 0;
	else if (key_code == XK_D)
		m->player.motion_ew = 0;
	else if (key_code == XK_LEFT)
		m->player.motion_rot = 0;
	else if (key_code == XK_RIGHT)
		m->player.motion_rot = 0;
	else if (key_code == XK_SPACE)
	{
		to_check = get_type(m);
		if (*to_check == '2')
			*to_check = 'D';
		else if (*to_check == 'D' && current != to_check)
			*to_check = '2';
	}
	return (0);
}

/* testx = m->player.pos_x + m->player.dir_x
	* (MOVE_SPEED * 10);
testy = m->player.pos_y + m->player.dir_y
	* (MOVE_SPEED * 10); */
char	*get_type(t_mlx *m)
{
	double	testx;
	double	testy;
	char	*c;

	testx = m->player.pos_x + (1 * m->player.dir_x);
	testy = m->player.pos_y + (1 * m->player.dir_y);
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
 * @brief rotates the camera in y axis with the mouse
 * @note MAC version
  */
int	mouse_rotation_bonus(int x, int y, t_mlx *m)
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
}

/**
 * @brief rotates the camera in y axis with the mouse
 * @note Linux version
  */
/* int	mouse_rotation_bonus(int x, int y, t_mlx *m)
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
} */
