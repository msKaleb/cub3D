
#include "ft_cub3d.h"

static void validate_pos(t_player *player, double next_x, double next_y)
{
	if (player->map[(int)next_y][(int)next_x] == '0')
	{
		player->pos_x = next_x;
		player->pos_y = next_y;
	}
}

/**
 * @brief initialize the struct with parameters from the map
 * @note why do I have to add .5 to pos_x/y???
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
}

int	has_to_move(int key_code)
{
	long	*keys;
	int		i;

	i = -1;
	keys = (long [6]){XK_W, XK_A, XK_S, XK_D, XK_LEFT, XK_RIGHT};
	while (++i < 6)
		if (key_code == keys[i])
			return (1);
	return (0);
}
void	move_player(t_mlx *m, int key_code)
{
	double	next_x;
	double	next_y;

	if (key_code == XK_W)
	{
		next_x = m->player.pos_x + m->player.dir_x * MOVE_SPEED;
		next_y = m->player.pos_y + m->player.dir_y * MOVE_SPEED;
	}
	if (key_code == XK_S)
	{
		next_x = m->player.pos_x - m->player.dir_x * MOVE_SPEED;
		next_y = m->player.pos_y - m->player.dir_y * MOVE_SPEED;
	}
	if (key_code == XK_A)
	{
		next_x = m->player.pos_x +  m->player.dir_y * MOVE_SPEED;
		next_y = m->player.pos_y -  m->player.dir_x * MOVE_SPEED;
	}
	if (key_code == XK_D)
	{
		next_x = m->player.pos_x -  m->player.dir_y * MOVE_SPEED;
		next_y = m->player.pos_y +  m->player.dir_x * MOVE_SPEED;
	}
	validate_pos(&m->player, next_x, next_y);
}
