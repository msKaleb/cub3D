/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:05:04 by nimai             #+#    #+#             */
/*   Updated: 2024/01/05 15:08:21 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include "colors.h"

// #include "libft/libft.h"//for test

// typedef struct	s_point
// {
// 	int			x;
// 	int			y;
// }				t_point;

// void	flood_fill(char **tab, t_point size, t_point begin);

// /**
// * @brief obtain data in general (main structure)
// * @param tex_path[0]: noth
// * @param tex_path[1]: south
// * @param tex_path[2]: west
// * @param tex_path[3]: east
// */
// typedef struct s_data
// {
// 	t_point	map_size;
// 	// int		num_rows;
// 	// int		num_cols;
// 	int		num_person;
// 	int		pos_map;
// 	t_point	pt_person;
// 	int		dir_person;
// 	char	*tex_path[4];
// 	int		floor_col;
// 	int		ceiling_col;
// }	t_data;

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

static char *obtain_double_str(char *str, t_data *data, int nb_line)
{

	char	*ret;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = (ft_strlen(str) * 2);
	ret = (char *) ft_calloc(1, len);
	// printf("len :%ld\n", len);
	if (!ret)
	{
		errno = ENOMEM;
		return (NULL);
	}
	while (/*str[i] && i < ft_strlen(str) && */j < len + 1)
	{
		ret[j] = str[i];
		// printf("ret[%ld]: %c str[%ld]: %c\n", j, ret[j], i, str[i]);
		// printf("nb_line: %d data->map->size.y: %d\n", nb_line, data->map_size.y - 1);
		if (str[i] == 0 && nb_line == data->map_size.y - 1)
		{
			// printf(GREEN"nb_line: %d data->map->size.y: %d%s\n", nb_line, data->map_size.y - 1, RESET);
			ret[j] = 10;
		}
		if (str[i] != 10)
		{
			j++;
			ret[j] = str[i];
		}
		// printf("ret[%ld]: %c str[%ld]: %c\n", j, ret[j], i, str[i]);


		// printf("&ret[%ld]: %s\n", j, &ret[j]);
		// printf("&str[%ld]: %s\n", i, &str[i]);
		// printf("ret: %s\n", ret);
		// printf("&str[%ld]: %s\n", i, &str[i]);
		i++;
		j++;
	}
	ret[j] = '\0';
	// printf(GREEN "ret[%ld]: %s%s\n", j, ret, RESET);
	// printf(GREEN "str[%ld]: %s%s\n", i, str, RESET);
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
		return (NULL);//memory allocation error
	str = get_next_line(fd);
	while (str && i[1] < (*data)->map_size.y && i[2] < ((*data)->map_size.y * 2))
	{
		if (i[0] >= (*data)->pos_map)
		{
			ret[i[1]] = ft_strdup(str);
			(*data)->minimap[i[2]] = obtain_double_str(str, *data, i[0] - (*data)->pos_map);
			// printf("(*data)->minimap[%d]: %s\n", i[2], (*data)->minimap[i[2]]);
			(*data)->minimap[i[2] + 1] = obtain_double_str(str, *data, i[0] - (*data)->pos_map);
			// printf("(*data)->minimap[%d]: %s\n", i[2],(*data)->minimap[i[2]]);
			// (*data)->minimap[i[1]] = ft_strdup(str);
			if (!ret[i[1]] || !(*data)->minimap[i[2]] || !(*data)->minimap[++i[2]])
				return (/* free_2dimension(ret), */ NULL);
			replace_spaces(&ret[i[1]]);
			i[1]++;
			i[2]++;
		}
		// if (i[1] == 3)
		// 	exit(3);
		free(str);
		str = get_next_line(fd);
		i[0]++;
	}
	close (fd);
	return (ret);
}

char	**parser_bonus(char *map_name, t_data *data)
{
	char	**tab;
	int		fd;

	init_data(&data);
	if (check_map(&data, map_name) == -1)
		return (NULL);
	if (!data->num_person)
		return (printf("no person\n"), NULL);
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (/* free_2dimension(tab) */NULL);//error file open failed
	tab = obtain_map(&data, fd);
	if (!tab || !*tab)
		return (NULL);//error obtain_map failed
	flood_fill(tab, data->map_size, data->pt_person);
	if (is_overflow(tab, data) == -1)
		return (printf("%smap is not closed%s\n", RED, RESET),/* free_2dimension(tab) */NULL);//error
	return (tab);
}
