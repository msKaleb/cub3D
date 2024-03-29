/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:05:04 by nimai             #+#    #+#             */
/*   Updated: 2024/01/16 13:32:04 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include "colors.h"

static void	init_data(t_data **data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		(*data)->tex_path[i] = NULL;
	}
	(*data)->num_person = 0;
	(*data)->pos_map = 0;
	(*data)->map_size.x = 0;
	(*data)->map_size.y = 0;
	(*data)->pt_person.x = 0;
	(*data)->pt_person.y = 0;
	(*data)->map_end = 0;
	(*data)->ceiling_col = -1;
	(*data)->floor_col = -1;
	(*data)->blocksize = 3;
}

int	allocate_memories(t_data **data, char ***ret)
{
	(*data)->minimap = (char **)ft_calloc(((*data)->map_size.y * 2) + 1, \
	sizeof(char *));
	*ret = (char **)ft_calloc((*data)->map_size.y + 1, sizeof(char *));
	if (!*ret || !(*data)->minimap)
		return (free_2dimension(*ret), free_2dimension((*data)->minimap), -1);
	return (0);
}

static char	**obtain_map(t_data **data, int fd)
{
	int		i[3];
	char	**ret;
	char	*str;

	ft_bzero(i, sizeof(int) * 3);
	if (allocate_memories(data, &ret) == -1)
		return (close (fd), NULL);
	str = get_next_line(fd);
	while (str && i[1] < (*data)->map_size.y && i[2] < \
	((*data)->map_size.y * 2))
	{
		if (i[0] >= (*data)->pos_map)
		{
			if (obtain_map_minimap(str, ret, data, i) == -1)
				return (close (fd), free(str), NULL);
			i[1]++;
			i[2] += 2;
		}
		free(str);
		str = get_next_line(fd);
		i[0]++;
	}
	return (free (str), close (fd), ret);
}

void	obtain_y_minimap(t_data **data)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while ((*data)->minimap[i] && is_brank((*data)->minimap[i]))
		i++;
	(*data)->pos_map = i;
	while ((*data)->minimap[i])
	{
		if (is_brank((*data)->minimap[i]))
		{
			while ((*data)->minimap[i] && is_brank((*data)->minimap[i]))
				i++;
			if (!(*data)->minimap[i])
				break ;
		}
		i++;
		ret++;
	}
	(*data)->map_size.y = ret;
}

char	**parser_bonus(char *map_name, t_data *data)
{
	char	**tab;
	int		fd;

	tab = NULL;
	init_data(&data);
	if (check_map_bonus(&data, map_name) == -1)
		return (NULL);
	if (!data->num_person)
		return (err_parse("no person"), NULL);
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (err_file(map_name), NULL);
	tab = obtain_map(&data, fd);
	if (!tab || !*tab)
		return (free_2dimension(data->minimap), free_2dimension(tab));
	flood_fill(tab, data->map_size, data->pt_person);
	if (is_overflow(tab, data) == -1)
		return (err_parse("map is not closed"), free_2dimension(tab));
	obtain_y_minimap(&data);
	return (tab);
}
