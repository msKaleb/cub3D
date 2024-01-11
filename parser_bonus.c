/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:05:04 by nimai             #+#    #+#             */
/*   Updated: 2024/01/11 15:42:56 by msoria-j         ###   ########.fr       */
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
	(*data)->ceiling_col = -1;
	(*data)->floor_col = -1;
	(*data)->blocksize = 3;
}

static char	*obtain_double_str(char *str, t_data *data, int nb_line)
{
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ret = (char *) ft_calloc(1, (ft_strlen(str) * 2));
	if (!ret)
	{
		errno = ENOMEM;
		return (NULL);
	}
	while (j < (ft_strlen(str) * 2 + 1))
	{
		if (is_brank(&str[i]))
		{
			ret [j++] = 10;
			break ;
		}
		ret[j] = str[i];
		if (str[i] == 0 && nb_line == data->map_size.y - 1)
			ret[j] = 10;
		if (str[i] != 10)
			ret[++j] = str[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	if ((int)ft_strlen(ret) > data->map_size.x)
		data->map_size.x = (int)ft_strlen(ret);
	return (ret);
}

static char	**obtain_map(t_data **data, int fd)
{
	int		i[3];
	char	**ret;
	char	*str;

	ft_bzero(i, sizeof(int) * 3);
	(*data)->minimap = (char **)ft_calloc(((*data)->map_size.y * 2) + 1, sizeof(char *));
	ret = (char **)ft_calloc((*data)->map_size.y + 1, sizeof(char *));
	if (!ret || !(*data)->minimap)
		return (close (fd), free_2dimension(ret), free_2dimension((*data)->minimap));//memory allocation error
	str = get_next_line(fd);
	while (str && i[1] < (*data)->map_size.y && i[2] < ((*data)->map_size.y * 2))
	{
		if (i[0] >= (*data)->pos_map)
		{
			ret[i[1]] = ft_strdup(str); // leaks
			(*data)->minimap[i[2]] = obtain_double_str(str, *data, i[0] - (*data)->pos_map);
			(*data)->minimap[i[2] + 1] = obtain_double_str(str, *data, i[0] - (*data)->pos_map);
			if (!ret[i[1]] || !(*data)->minimap[i[2]] || !(*data)->minimap[++i[2]])
				return (close (fd), free_2dimension(ret), free_2dimension((*data)->minimap));
			replace_spaces(&ret[i[1]]);
			i[1]++;
			i[2]++;
		}
		free(str);
		str = get_next_line(fd);
		i[0]++;
	}
	close (fd);
	return (ret);
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
		return (printf("no person\n"), NULL);
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (free_2dimension(tab));//error file open failed
	tab = obtain_map(&data, fd);
	if (!tab || !*tab)
		return (free_2dimension(tab), free_2dimension(data->minimap));//error obtain_map failed
	// for (int i = 0; data->minimap[i]; i++)
	// {
	// 	printf("%s", data->minimap[i]);
	// }
	flood_fill(tab, data->map_size, data->pt_person);
	if (is_overflow(tab, data) == -1)
		return (printf("%smap is not closed%s\n", RED, RESET), free_2dimension(tab), free_2dimension(data->minimap));//error
	obtain_y_minimap(&data);
	return (tab);
}
