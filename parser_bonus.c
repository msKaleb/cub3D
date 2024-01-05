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

static char	**obtain_map(t_data **data, int fd)
{
	int		i[2];
	char	**ret;
	char	*str;

	ft_bzero(i, sizeof(int) * 2);
	(*data)->minimap = (char **)ft_calloc((*data)->map_size.y + 1, sizeof(char *));
	ret = (char **)ft_calloc((*data)->map_size.y + 1, sizeof(char *));
	if (!ret || !(*data)->minimap)
		return (NULL);//memory allocation error
	str = get_next_line(fd);
	while (str && i[1] < (*data)->map_size.y)
	{
		if (i[0] >= (*data)->pos_map)
		{
			ret[i[1]] = ft_strdup(str);
			(*data)->minimap[i[1]] = ft_strdup(str);
			if (!ret[i[1]] || !(*data)->minimap[i[1]])
				return (/* free_2dimension(ret), */ NULL);
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
	// for(int i = 0; tab[i]; i++)
	// {
	// 	printf("%s", tab[i]);
	// }
	// printf("\n\nfinish write map\n");
	// for(int i = 0; data->minimap[i]; i++)
	// {
	// 	printf("%s", data->minimap[i]);
	// }
	// printf("\n\nfinish write map\n");
	flood_fill(tab, data->map_size, data->pt_person);
	if (is_overflow(tab, data) == -1)
		return (printf("%smap is not closed%s\n", RED, RESET),/* free_2dimension(tab) */NULL);//error
	return (tab);
}
