/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:05:04 by nimai             #+#    #+#             */
/*   Updated: 2024/01/03 22:25:21 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"
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

int	check_file_format(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strcmp(".cub", str + (len - 4)))
	{
		printf("not cub\n");
		return (-1);
	}
	return (0);
}

int	get_direction(char c)
{
	int	ret;

	ret = 0;
	if (c == 'N')
		ret = 0;
	if (c == 'S')
		ret = 180;
	if (c == 'W')
		ret = 270;
	if (c == 'E')
		ret = 90;
	return (ret);
}

int	count_cols(t_data **data, char *line)
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
int	check_paths(t_data *data, t_raycast *ray)
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
	if (ray->ceiling_col == -1 || ray->floor_col == -1)
	{
		// printf("%sI don't have enough colour%s\n", GREEN, RESET);
		return (0);
	}
	return (1);
}

int	is_brank(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] != 32 && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

/**
  *@param pos[0]: start pos
  *@param pos[1]: end pos
  *@param pos[2]: colour position
  *@note convert rgb to colour in dicimal
  */
int	get_rgb(char *str)
{
	int		pos[3];
	int		colour[3];
	char	*tmp;
	int		ret;

	ft_bzero(pos, sizeof(int) * 3);
	ft_bzero(colour, sizeof(int) * 3);
	while (str[pos[0]] && pos[2] < 3)
	{
		while (str[pos[0]] && str[pos[0]] == 32)
			pos[0]++;
		if (!ft_isdigit(str[pos[0]]))
			return (printf("colour is not digit\n"), -1);//error
		pos[1] = pos[0];
		while (str[pos[1]] && ft_isdigit(str[pos[1]])/* str[pos[1]] != 32, str[pos[1]] != ',' */)
			pos[1]++;
		tmp = ft_substr(str, pos[0], pos[1] - pos[0]);
		// printf("tmp* %s\n", tmp);
		colour[pos[2]] = ft_atoi(tmp);
		free (tmp);
		if (colour[pos[2]] < 0 || colour[pos[2]] > 255)
			return (printf("colour is out of range\n"), -1);//error
		pos[2]++;
		pos[0] = pos[1] + 1;
	}
	//I need protect from some garbage after colour??
	if (pos[2] != 3)
		return (printf("lack of information for colour\n"), -1);//error OR we can put 0 instead of return error
	if (!is_brank(&str[pos[0]]))
		return (printf("I have more than I should have\n"), -1);//error OR we can put 0 instead of return error
	ret = (colour[0] << 16) + (colour[1] << 8) + (colour[2]);
	// printf("ret: %d\n", ret);
	return (ret);
}

int	obtain_path(t_data **data, char *line, t_raycast **ray)
{
	int	i;
	// int	colour;

	i = 0;
	// colour = 0;
	//move to the next line if there is only '\n'
	if (!line || (line[i] && line[i] == 10))
		return (1);
	//skip while there are spaces
	while (line[i] && line[i] == 32)
		i++;
	if (!ft_strncmp(&line[i], "NO ", 3))
		return ((*data)->tex_path[0] = ft_strdup(line + (i + 3)), 0);
	else if (!ft_strncmp(&line[i], "SO ", 3))
		return ((*data)->tex_path[1] = ft_strdup(line + (i + 3)), 0);
	else if (!ft_strncmp(&line[i], "WE ", 3))
		return ((*data)->tex_path[2] = ft_strdup(line + (i + 3)), 0);
	else if (!ft_strncmp(&line[i], "EA ", 3))
		return ((*data)->tex_path[3] = ft_strdup(line + (i + 3)), 0);
	else if (!ft_strncmp(&line[i], "F ", 2))
		return ((*ray)->floor_col = get_rgb(line + (i + 2)));
	else if (!ft_strncmp(&line[i], "C ", 2))
		return ((*ray)->ceiling_col = get_rgb(line + (i + 2)));
	return (-1);
}

int	check_map(t_data **data, char *map_name, t_raycast **ray)
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
		// printf("%s", line);
		if (check_paths(*data, *ray) && !is_brank(line))
		{
			if (!(*data)->pos_map)
				(*data)->pos_map = i;
			if (count_cols(data, line) == -1)
				return (close(fd), free (line), -1);
			(*data)->map_size.y++;
		}
		else
			if (obtain_path(data, line, ray) == -1)
				return (close(fd), free (line), -1);//error path incorrect
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (close(fd), 0);
}

void	replace_spaces(char **str)
{
	int	i;

	i = 0;
	// printf("replace: \n%s", *str);
	while ((*str)[i])
	{
		if ((*str)[i] == 32)
			(*str)[i] = '0';
		if ((*str)[i] >= 'E' && (*str)[i] <= 'W')
			(*str)[i] = '0';
		i++;
	}
}

int	is_overflow(char **map, t_data *data)
{
	int	i;

	i = 0;
	while (map[data->map_size.y - 1 - i][0] == '\n')
		i++;
	if (ft_strchr(map[0], 'F') || ft_strchr(map[data->map_size.y - 1 - i], 'F'))
	{
		printf("the first or the last line\n");
		return (-1);
	}
	i = 0;
	while (map[i] && i < data->map_size.y)
	{
		if (map[i][0] == 'F' || map[i][(int)ft_strlen(map[i]) - 2] == 'F')
		{
			printf("the right or the left edge\n");
			return (-1);
		}
		i++;
	}
	return (1);
}

void	init_data(t_data **data)
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
}

char	**obtain_map(t_data **data, int fd)
{
	int		i[2];
	char	**ret;
	char	*str;

	ft_bzero(i, sizeof(int) * 2);
	ret = (char **)ft_calloc((*data)->map_size.y + 1, sizeof(char *));
	if (!ret)
		return (NULL);//memory allocation error
	str = get_next_line(fd);
	while (str && i[1] < (*data)->map_size.y)
	{
		if (i[0] >= (*data)->pos_map)
		{
			ret[i[1]] = ft_strdup(str);
			if (!ret[i[1]])
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

char	**parser(char *map_name, t_data *data, t_raycast *ray)
{
	char	**tab;
	int		fd;

	init_data(&data);
	fd = 0;
	if (check_map(&data, map_name, &ray) == -1)
		return (NULL);
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (/* free_2dimension(tab) */NULL);//error file open failed
	tab = obtain_map(&data, fd);
	if (!tab)
		return (NULL);//error obtain_map failed
	flood_fill(tab, data->map_size, data->pt_person);
	if (is_overflow(tab, data) == -1)
		return (printf("%smap is not closed%s\n", RED, RESET),/* free_2dimension(tab) */NULL);//error
	return (tab);
}



// int	main(int ac, char **argv)
// {
// 	t_data	data;
// 	int		fd;

// 	ft_bzero(&data, 1 * sizeof(t_data));
// 	fd = 0;
// 	if (ac != 2)
// 	{
// 		printf("bad argument\n");
// 		return (-1);//error bad argument
// 	}
// 	//check format;
// 	if (check_file_format(argv[1]) == -1)
// 		return (-2);//error incorrect file format 
// 		/* parser */
// 	char	**map;
// 	map = parser(argv[1], &data);
// 	if (!map)
// 	{
// 		//free
// 		printf("failed parser\n");
// 		return(1);//
// 	}
// 	printf("output after parser\n");
// 	for (int i = 0; map[i]; i++)
// 		printf("%s", map[i]);
// 	/*  */

// 	printf("\ndone all lines in main\n");
// 	return (0);
// }
