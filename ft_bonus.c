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
		else if (line[i] == '3')
			(*data)->num_sprite++;
		else if (line[i] && !(line[i] >= '0' && line[i] <= '3') && line[i] != 32 && line[i] != 10)
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

int	obtain_path_bonus(t_data **data, char *line)
{
	int	i;

	i = 0;
	//move to the next line if there is only '\n'

	//240110 has been removed
	// if (!line || (line[i] && line[i] == 10))
	// 	return (1);

	while (line[i] && is_space(line[i]))
		i++;
	if (!line || !line[i] || (line[i] && line[i] == 10))
		return (1);
	if (!(*data)->tex_path[0] && !ft_strncmp(&line[i], "NO ", 3))
		return ((*data)->tex_path[0] = ft_strdup(line + (i + 3)), 0);
	else if (!(*data)->tex_path[1] && !ft_strncmp(&line[i], "SO ", 3))
		return ((*data)->tex_path[1] = ft_strdup(line + (i + 3)), 0);
	else if (!(*data)->tex_path[2] && !ft_strncmp(&line[i], "WE ", 3))
		return ((*data)->tex_path[2] = ft_strdup(line + (i + 3)), 0);
	else if (!(*data)->tex_path[3] && !ft_strncmp(&line[i], "EA ", 3))
		return ((*data)->tex_path[3] = ft_strdup(line + (i + 3)), 0);
	else if (!(*data)->tex_path[4] && !ft_strncmp(&line[i], "S1 ", 3))
		return ((*data)->tex_path[4] = ft_strdup(line + (i + 3)), 0);
	else if (!(*data)->tex_path[5] && !ft_strncmp(&line[i], "S2 ", 3))
		return ((*data)->tex_path[5] = ft_strdup(line + (i + 3)), 0);
	else if (!(*data)->tex_path[6] && !ft_strncmp(&line[i], "S3 ", 3))
		return ((*data)->tex_path[6] = ft_strdup(line + (i + 3)), 0);
	else if ((*data)->floor_col == -1 && !ft_strncmp(&line[i], "F ", 2))
		return ((*data)->floor_col = get_rgb(line + (i + 2)));
	else if ((*data)->ceiling_col == -1 && !ft_strncmp(&line[i], "C ", 2))
		return ((*data)->ceiling_col = get_rgb(line + (i + 2)));
	return (-1);
}

/**
 *@note check before start the main map
 *@note 240111nimai: at this moment, texture for stripe is required as well
  */
static int	check_paths_bonus(t_data *data)
{
	int	i;

	i = 0;
	while (i < MAX_TEXTURES)
	{
		if (data->tex_path[i] == NULL)
		{
			// printf("%sI don't have enough texture%s\n", GREEN, RESET);
			return (0);
		}
		i++;
	}
	if (data->ceiling_col == -1 || data->floor_col == -1)
	{
		// printf("%sI don't have enough colour%s\n", GREEN, RESET);
		return (0);
	}
	return (1);
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
		if (check_paths_bonus(*data)/*  && !is_brank(line) */)
		{
			if (check_each_line_bonus(data, line, i) == -1)
				return (close(fd), free (line), -1);
		}
		else
			if (obtain_path_bonus(data, line) == -1)
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
 * @brief calculates the next position of the player
 * and checks if it's inside a wall (collisions)
  */
void	move_player_bonus(t_mlx *m)
{
	double	next_x;
	double	next_y;

	// this is to check what kind of square is in front of us 
	// TODO put into another function
	// {
	// 	double	testx, testy;
	// 	testx = m->player.pos_x + m->player.dir_x
	// 		* (MOVE_SPEED);
	// 	testy = m->player.pos_y + m->player.dir_y
	// 		* (MOVE_SPEED);
	// 	ft_fprintf(1, "type: %c\n", m->player.map[(int)testy][(int)testx]);
	// }

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
	if (m->player.map[(int)next_y][(int)next_x] == 'F') // && '2' when flag == open
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
		m->player.motion_rot = -2;
	else if (m->cur.x < x - 2)
		m->player.motion_rot = 2;
	else
		m->player.motion_rot = 0;
	m->cur.x = x;
	m->cur.y = y;
	return (0);
}
