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
