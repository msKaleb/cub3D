/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:05:04 by nimai             #+#    #+#             */
/*   Updated: 2023/12/31 14:06:38 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_cub3d.h"
#include <fcntl.h>
#include <stdio.h>
#include "colors.h"

#include "libft/libft.h"//for test

# define GREEN			"\033[32m"				/* Green */
# define RESET			"\033[0m"


typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

void	flood_fill(char **tab, t_point size, t_point begin);

/**
* @brief obtain data in general (main structure)
* @param tex_path[0]: noth
* @param tex_path[1]: south
* @param tex_path[2]: west
* @param tex_path[3]: east
*/
typedef struct s_data
{
	int		num_rows;
	int		num_cols;
	int		num_person;
	int		pos_map;
	t_point	pt_person;
	int		dir_person;
	char	*tex_path[4];
	int		floor_col;
	int		ceiling_col;
}	t_data;

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

void	count_cols(t_data **data, char *line)
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
			(*data)->pt_person.y = (*data)->num_rows;
			(*data)->dir_person = get_direction(line[i]);
		}
		else if (line[i] && line[i] != '0' && line[i] != '1' && line[i] != 32 && line[i] != 10)
		{
			printf("LINE: %d where am i?? line[i]: %d\n", __LINE__, line[i]);
			exit(-1);//map invalid (wrong letter)
		}
	}
	if ((*data)->num_person > 1)
	{
		printf("LINE: %d where am i?? line[i]: %d\n", __LINE__, line[i]);
		exit(-1);//map invalid (more than 1 person);
	}
	if (i > (*data)->num_cols)
		(*data)->num_cols = i;
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
			printf("I don't have enough texture\n");
			return (0);
		}
		i++;
	}
	if (!data->ceiling_col || !data->floor_col)
	{
		printf("I don't have enough colour\n");
		return (0);
	}
	return (1);
}

/**
  *@param pos[0]: start pos
  *@param pos[1]: end pos
  *@param pos[2]: colour position
  */
int	get_cols(char *str)
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
			return (printf("colour is not digit"), -1);//error
		pos[1] = pos[0];
		while (str[pos[1]] && ft_isdigit(str[pos[1]])/* str[pos[1]] != 32, str[pos[1]] != ',' */)
			pos[1]++;
		tmp = ft_substr(str, pos[0], pos[1] - pos[0]);
		// printf("tmp* %s\n", tmp);
		colour[pos[2]] = ft_atoi(tmp);
		free (tmp);
		if (colour[pos[2]] < 0 || colour[pos[2]] > 255)
			return (printf("colour is out of range"), -1);//error
		pos[2]++;
		pos[0] = pos[1] + 1;// I think it's on the comma, so one step ahead
	}
	//I need protect from some garbage after colour??
	if (pos[2] != 3)
		return (printf("lack of information for colour"), -1);//error OR we can put 0 instead of return error
	// printf("colour[0]: %d\n", colour[0]);
	// printf("colour[1]: %d\n", colour[1]);
	// printf("colour[2]: %d\n", colour[2]);
	ret = (colour[0] << 16) + (colour[1] << 8) + (colour[2]);
	printf("ret: %d\n", ret);
	return (ret);
}

int	obtain_path(t_data **data, char *line)
{
	int	i;

	i = 0;
	//move to the next line if there is only '\n'
	if (line[i] && line[i] == 10)
		return (1);
	//skip while there are spaces
	while (line[i] && line[i] == 32)
		i++;
	if (&line[i] && !ft_strncmp(&line[i], "NO ", 3))
		return ((*data)->tex_path[0] = ft_strdup(line + (i + 3)), 0);
	else if (&line[i] && !ft_strncmp(&line[i], "SO ", 3))
		return ((*data)->tex_path[1] = ft_strdup(line + (i + 3)), 0);
	else if (&line[i] && !ft_strncmp(&line[i], "WE ", 3))
		return ((*data)->tex_path[2] = ft_strdup(line + (i + 3)), 0);
	else if (&line[i] && !ft_strncmp(&line[i], "EA ", 3))
		return ((*data)->tex_path[3] = ft_strdup(line + (i + 3)), 0);
	else if (&line[i] && !ft_strncmp(&line[i], "F ", 2))
		return ((*data)->floor_col = get_cols(line + (i + 2)), 0);
	else if (&line[i] && !ft_strncmp(&line[i], "C ", 2))
		return ((*data)->ceiling_col = get_cols(line + (i + 2)), 0);
	return (-1);
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

int	check_map(t_data **data, char *map_name)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		// exit (err_file(map_name));//to compile with errors.c
		return (-1);//error file open failed
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		//
		//also it's neccessary check if there are NO, SU, WE, EA, C, and F before map
		//
		printf("%s", line);
		if (check_paths(*data) && !is_brank(line))//if it returns 1
		{
			printf("result is_brank %d\n", is_brank(line));
			if (!(*data)->pos_map)
				(*data)->pos_map = i;
			count_cols(data, line);
			(*data)->num_rows++;
		}
		else
		{
			if (obtain_path(data, line) == -1)
				return (close(fd), free (line), -1);//error path incorrect
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	printf("(*data)->pos_map: %d\n", (*data)->pos_map);
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
		if ((*str)[i] == 'N' || (*str)[i] == 'S' || (*str)[i] == 'W' || (*str)[i] == 'E')
			(*str)[i] = '0';
		i++;
	}
}

int	is_overflow(char **map, t_data *data)
{
	int	i;

	i = 0;
	//the first line, the last line check
	
	//skip until the wall
	while (map[data->num_rows - 1 - i][0] == '\n')
		i++;
	if (ft_strchr(map[0], 'F') || ft_strchr(map[data->num_rows - 1 - i], 'F'))
	{
		printf("the first\n");
		return (-1);
	}
	i = 0;
	//check each line the first letter and the last(without '\n')
	while (map[i] && i < data->num_rows)
	{
		if (map[i][0] == 'F' || map[i][(int)ft_strlen(map[i]) - 2] == 'F')
		{
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
	(*data)->ceiling_col = 0;
	(*data)->floor_col = 0;
	/**
	* @note CHECK! it's initialized as 0 at home, how about MAC?
	  */
	printf("pos_map: %d\n", (*data)->pos_map);
}

char	**parser(char *map_name, t_data *data)
{
	char	**tab;
	int		i[2];
	char 	*str;
	int		fd = 0;

	init_data(&data);
	if (check_map(&data, map_name) == -1)
	{
		printf("Im not here??\n");	
		return (NULL);
	}
	ft_bzero(i, sizeof(int) * 2);
	//DELETE
	// printf("check! check_map\n");
	// printf("data->row: %d\ndata->cols: %d\ndata->person: %d\n", data->num_rows, data->num_cols, data->num_person);
	// data->num_rows = count_rows(map_name);
	
	tab = (char **)ft_calloc(data->num_rows + 1, sizeof(char *));
	if (!tab)
		return (NULL);//memory allocation error	
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		printf("open failed\n");
		exit(-3);//error file open failed
	}
	// printf("Line: %d tab: %p\n", __LINE__, tab);
	str = get_next_line(fd);
	printf("%s\ncheck result of replace spaces!!%s\n", BLUE, RESET);
	while (str && i[1] < data->num_rows)
	{
		if (i[0] >= data->pos_map)
		{
			tab[i[1]] = ft_strdup(str);
			if (!tab[i[1]])
				return (/* free_2dimension(tab), */ NULL);
			replace_spaces(&tab[i[1]]);
			i[1]++;
		}
		// printf("%s", tab[i]);
		free(str);
		str = get_next_line(fd);
		i[0]++;
	}

	t_point	size;

	size.x = data->num_cols;
	size.y = data->num_rows;

	printf("\ncheck result of flood fill!!\n");

	flood_fill(tab, size, data->pt_person);
	if (is_overflow(tab, data) == -1)
	{
		//free memory
		// free_2dimension(tab);
		printf("map is invalid!\n");
		return (NULL);//error
	}
	return (tab);
}



int	main(int ac, char **argv)
{
	t_data	data;
	int		fd;

	ft_bzero(&data, 1 * sizeof(t_data));
	fd = 0;
	if (ac != 2)
	{
		printf("bad argument\n");
		return (-1);//error bad argument
	}
	//check format;
	if (check_file_format(argv[1]) == -1)
		return (-2);//error incorrect file format 
		/* parser */
	char	**map;
	map = parser(argv[1], &data);
	if (!map)
		return(1);//
	printf("output after parser\n");
	for (int i = 0; map[i]; i++)
		printf("%s", map[i]);
	/*  */
	return (0);
}
