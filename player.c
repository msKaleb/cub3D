/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:59:45 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/03 14:12:38 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static void	validate_pos(t_player *player, double next_x, double next_y)
{
	if (player->map[(int)next_y][(int)next_x] == '0')
	{
		player->pos_x = next_x;
		player->pos_y = next_y;
	}
}

/**
 * @brief initialize the struct with parameters from the map
 * @note add .5 to the position to place it in the center of the tile
 * @todo change pos_x/y to the values on the map, now is for testing
  */
void	init_player(t_player *player)
{
	t_initial_dir	dir;

	if (player->dir == 'N')
		dir = (t_initial_dir){{0, -1, 1, 0}};
	else if (player->dir == 'S')
		dir = (t_initial_dir){{0, 1, -1, 0}};
	else if (player->dir == 'W')
		dir = (t_initial_dir){{-1, 0, 0, -1}};
	else if (player->dir == 'E')
		dir = (t_initial_dir){{1, 0, 0, 1}};
	player->pos_x = 17.5;
	player->pos_y = 8.5;
	player->dir_x = 0 + dir.orientation[0];
	player->dir_y = 0 + dir.orientation[1];
	player->plane_x = 0.66 * dir.orientation[2];
	player->plane_y = 0.66 * dir.orientation[3];
	player->motion_ns = 0;
	player->motion_ew = 0;
	player->motion_rot = 0;
}

/* int	has_to_move(int key_code)
{
	long	*keys;
	int		i;

	i = -1;
	keys = (long [6]){XK_W, XK_A, XK_S, XK_D, XK_LEFT, XK_RIGHT};
	while (++i < 6)
		if (key_code == keys[i])
			return (1);
	return (0);
} */

void	move_player(t_mlx *m/* , int key_code */)
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
	validate_pos(&m->player, next_x, next_y);
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
		m->player.dir_x = dir_x * cos(ROTATION_SPEED * m->player.motion_rot) - m->player.dir_y * sin(ROTATION_SPEED * m->player.motion_rot);
		m->player.dir_y = dir_x * sin(ROTATION_SPEED * m->player.motion_rot) + m->player.dir_y * cos(ROTATION_SPEED * m->player.motion_rot);
		m->player.plane_x = plane_x * cos(ROTATION_SPEED * m->player.motion_rot) - m->player.plane_y * sin(ROTATION_SPEED * m->player.motion_rot);
		m->player.plane_y = plane_x * sin(ROTATION_SPEED * m->player.motion_rot) + m->player.plane_y * cos(ROTATION_SPEED * m->player.motion_rot);
	}
	/* if (key_code == XK_LEFT)
		dir = -1;
	else if (key_code == XK_RIGHT)
		dir = 1;
	else
		return ;
	rot = ROTATION_SPEED * dir;
	m->player.dir_x = dir_x * cos(rot) - m->player.dir_y * sin(rot);
	m->player.dir_y = dir_x * sin(rot) + m->player.dir_y * cos(rot);
	m->player.plane_x = plane_x * cos(rot) - m->player.plane_y * sin(rot);
	m->player.plane_y = plane_x * sin(rot) + m->player.plane_y * cos(rot); */
}

int		set_motion(int key_code, t_mlx *m)
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
		m->player.motion_rot= 1;
	render_frame(m);
	return (0);
}

int	release_motion(int key_code, t_mlx *m)
{
	if (key_code == XK_W)
		m->player.motion_ns = 0;
	else if (key_code == XK_S)
		m->player.motion_ns = -0;
	else if (key_code == XK_A)
		m->player.motion_ew = -0;
	else if (key_code == XK_D)
		m->player.motion_ew = 0;
	else if (key_code == XK_LEFT)
		m->player.motion_rot = -0;
	else if (key_code == XK_RIGHT)
		m->player.motion_rot= 0;
	return (0);
}