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
	render_frame_bonus(m);
	return (0);
}

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
	if (m->player.map[(int)next_y][(int)next_x] == 'F')
	{
		m->player.pos_x = next_x;
		m->player.pos_y = next_y;
	}
}

int	mouse_rotation_bonus(int x, int y, t_mlx *m)
{
	int	chunk = (DEFAULT_X / 2) / 10;
	int speed;

	speed = -(10 - (x / chunk)) / 3;
	
	if (x < 0)
		mlx_mouse_move(m->win, 0, y);
	else if (x > DEFAULT_X)
		mlx_mouse_move(m->win, DEFAULT_X, y);
	if (x < (DEFAULT_X / 2))
		m->player.motion_rot = speed;
	else if (x > (DEFAULT_X / 2))
		m->player.motion_rot = speed;
	if (m->cur.x == x)
		m->player.motion_rot = 0;
	m->cur.x = x;
	m->cur.y = y;
	return (0);
}
