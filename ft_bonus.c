#include "ft_cub3d_bonus.h"

static int	count_cols_bonus(t_data **data, char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		// printf("LINE: %d where am i?? line[i]: %c\n", __LINE__, line[i]);
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
		{
			// printf("LINE: %d where am i??\n", __LINE__);
			(*data)->num_person++;
			(*data)->pt_person.x = i;
			(*data)->pt_person.y = (*data)->map_size.y;
			(*data)->dir_person = line[i];
		}
		else if (line[i] && line[i] != '0' && line[i] != '1' && line[i] != '2' && line[i] != 32 && line[i] != 10)
		{
			printf("%sMap has invalid letter%s\n", RED, RESET);
			return(-1);//map invalid (wrong letter)
		}
	}
	if ((*data)->num_person > 1)
		return (-1);//map invalid (more than 1 person);
	if (i > (*data)->map_size.x)
		(*data)->map_size.x = i;
	return (0);
}

static int	check_each_line_bonus(t_data **data, char *line, int i)
{
	if (!(*data)->pos_map)
		(*data)->pos_map = i;
	if (count_cols_bonus(data, line) == -1)
		return (-1);
	(*data)->map_size.y++;
	return (0);
}

int	check_map_bonus(t_data **data, char *map_name)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (-1);//error file open failed
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (check_paths(*data)/*  && !is_brank(line) */)
		{
			if (check_each_line_bonus(data, line, i) == -1)
				return (close(fd), free (line), -1);
		}
		else
			if (obtain_path(data, line) == -1)
				return (close(fd), free (line), -1);//error path incorrect
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (close(fd), 0);
}

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

/**
 * @brief set of events on key release
  */
int	release_motion_bonus(int key_code, t_mlx *m)
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
		m->player.motion_rot = 0;
	else if (key_code == XK_SPACE)
		if (get_type(m) == 2){
			m->player.map[m->ray.map_y][m->ray.map_x] = 'D';
			ft_fprintf(1, "Door!\n");}
	return (0);
}

int	get_type(t_mlx *m)
	{
		double	testx, testy;
		char	c;

		testx = m->player.pos_x + m->player.dir_x
			* (MOVE_SPEED);
		testy = m->player.pos_y + m->player.dir_y
			* (MOVE_SPEED);
		// ft_fprintf(1, "type: %c\n", m->player.map[(int)testy][(int)testx]);
		c = m->player.map[(int)testy][(int)testx];
		// if (c == 'D') // fails
		// 	c = '2';
		return (c - '0');
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
	if (ft_strchr("FD", m->player.map[(int)next_y][(int)next_x])) // && '2' when flag == open
	{
		m->player.pos_x = next_x;
		m->player.pos_y = next_y;
	}
}

/**
 * @brief rotates the camera in y axis with the mouse
  */
int	mouse_rotation_bonus(int x, int y, t_mlx *m)
{
	if (x < 10) // in MAC (x < 0)
		// mlx_mouse_move(m->win, DEFAULT_X, y); // MAC version
		mlx_mouse_move(m->mlx, m->win, DEFAULT_X - 11, y); // Linux version
	else if (x > DEFAULT_X - 10) // in MAC (x > DEFAULT_X)
		// mlx_mouse_move(m->win, 0, y); // MAC version
		mlx_mouse_move(m->mlx, m->win, 11, y); // Linux version
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
