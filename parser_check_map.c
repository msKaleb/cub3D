/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:15:59 by nimai             #+#    #+#             */
/*   Updated: 2024/01/10 16:17:56 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"
#include "colors.h"
#include <fcntl.h>
#include <stdio.h>

static int	count_cols(t_data **data, char *line)
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
		else if (line[i] && line[i] != '0' && line[i] != '1' && line[i] != 32 && line[i] != 10)
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

/**
 *@note check before start the main map
  */
int	check_paths(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
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

int	obtain_path(t_data **data, char *line)
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
	else if ((*data)->floor_col == -1 && !ft_strncmp(&line[i], "F ", 2))
		return ((*data)->floor_col = get_rgb(line + (i + 2)));
	else if ((*data)->ceiling_col == -1 && !ft_strncmp(&line[i], "C ", 2))
		return ((*data)->ceiling_col = get_rgb(line + (i + 2)));
	return (-1);
}

static int	check_each_line(t_data **data, char *line, int i)
{
	if (!(*data)->pos_map)
		(*data)->pos_map = i;
	if (count_cols(data, line) == -1)
		return (-1);
	(*data)->map_size.y++;
	return (0);
}

int	check_map(t_data **data, char *map_name)
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
			if (check_each_line(data, line, i) == -1)
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
