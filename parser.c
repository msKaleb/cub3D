/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:05:04 by nimai             #+#    #+#             */
/*   Updated: 2024/01/13 13:08:43 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

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
	(*data)->ceiling_col = -1;
	(*data)->floor_col = -1;
}

static char	**obtain_map(t_data **data, int fd)
{
	int		i[2];
	char	**ret;
	char	*str;

	ft_bzero(i, sizeof(int) * 2);
	ret = (char **)ft_calloc((*data)->map_size.y + 1, sizeof(char *));
	if (!ret)
		return (close (fd), err_parse("failed alloc memory"), NULL);
	str = get_next_line(fd);
	while (str && i[1] < (*data)->map_size.y)
	{
		if (i[0] >= (*data)->pos_map)
		{
			ret[i[1]] = ft_strdup(str);
			if (!ret[i[1]])
				return (close (fd), err_parse("failed obtain map"), free_2dimension(ret));
			replace_spaces(&ret[i[1]]);
			i[1]++;
		}
		free(str);
		str = get_next_line(fd);
		i[0]++;
	}
	close (fd);
	return (ret);
}

char	**parser(char *map_name, t_data *data)
{
	char	**tab;
	int		fd;

	init_data(&data);
	if (check_map(&data, map_name) == -1)
		return (NULL);
	if (!data->num_person)
		return (err_parse("no person"), NULL);
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (err_file(map_name), NULL);
	tab = obtain_map(&data, fd);
	if (!tab || !*tab)
		return (free_2dimension(tab));
	flood_fill(tab, data->map_size, data->pt_person);
	if (is_overflow(tab, data) == -1)
		return (err_parse("map is not closed"), free_2dimension(tab));
	return (tab);
}
