/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:20:30 by nimai             #+#    #+#             */
/*   Updated: 2024/01/16 13:36:27 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d_bonus.h"

static char	*obtain_double_str(char *str, t_data *data, int nb_line)
{
	char	*ret;
	size_t	i[2];

	ft_bzero(i, 2 * sizeof(size_t));
	ret = (char *) ft_calloc(1, (ft_strlen(str) * 2));
	if (!ret)
		return (err_parse("failed alloc memory"), NULL);
	while (i[1] < (ft_strlen(str) * 2 + 1))
	{
		ret[i[1]] = str[i[0]];
		if (is_brank(&str[i[0]]))
		{
			ret [i[1]++] = 10;
			break ;
		}
		if (str[i[0]] == 0 && nb_line == data->map_size.y - 1)
			ret[i[1]] = 10;
		if (str[i[0]] != 10)
			ret[++i[1]] = str[i[0]];
		i[0]++;
		i[1]++;
	}
	if ((int)ft_strlen(ret) > data->map_size.x)
		data->map_size.x = (int)ft_strlen(ret);
	return (ret);
}

int	obtain_map_minimap(char *str, char **map, t_data **data, int i[3])
{
	map[i[1]] = ft_strdup(str);
	(*data)->minimap[i[2]] = obtain_double_str(str, *data, i[0] - \
	(*data)->pos_map);
	(*data)->minimap[i[2] + 1] = obtain_double_str(str, *data, i[0] - \
	(*data)->pos_map);
	if (!map[i[1]] || !(*data)->minimap[i[2]] || !(*data)->minimap[i[2] + 1])
	{
		free_2dimension(map);
		free_2dimension((*data)->minimap);
		return (err_parse("failed obtain map"));
	}
	replace_spaces(&map[i[1]]);
	return (0);
}

static int	count_cols_bonus(t_data **data, char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || \
		line[i] == 'E')
		{
			(*data)->num_person++;
			(*data)->pt_person.x = i;
			(*data)->pt_person.y = (*data)->map_size.y;
			(*data)->dir_person = line[i];
		}
		else if (line[i] && line[i] != '0' && line[i] != '1' && line[i] != '2' \
		&& line[i] != 32 && line[i] != 10)
			return (err_parse("Map has invalid letter"));
	}
	if ((*data)->num_person > 1)
		return (err_parse("Map has more than one player"));
	if (i > (*data)->map_size.x)
		(*data)->map_size.x = i;
	return (0);
}

static int	check_each_line_bonus(t_data **data, char *line, int i)
{
	if (line[0] == 10)
		return (0);
	if ((*data)->map_end == 1)
		return (err_parse("detected another line after newline"));
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

	i = -1;
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (err_file(map_name), -1);
	line = get_next_line(fd);
	while (line != NULL && ++i > -1)
	{
		if (check_paths(*data))
		{
			if (line[0] == 10 && (*data)->pos_map)
				(*data)->map_end = 1;
			else if (check_each_line_bonus(data, line, i) == -1)
				return (close(fd), free (line), -1);
		}
		else
			if (obtain_path(data, line) == -1)
				return (close(fd), free (line), -1);
		free(line);
		line = get_next_line(fd);
	}
	return (free (line), close(fd), 0);
}
