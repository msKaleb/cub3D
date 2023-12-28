/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:05:04 by nimai             #+#    #+#             */
/*   Updated: 2023/12/28 18:42:11 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_cub3d.h"
#include <fcntl.h>
#include <stdio.h>

#include "libft/libft.h"//for test


typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

void	flood_fill(char **tab, t_point size, t_point begin);

/**
* @brief obtain data in general (main structure)
*/
typedef struct s_data
{
	int		num_rows;
	int		num_cols;
	int		num_person;
	t_point	pt_person;
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

void	check_map(t_data **data, char *map_name)
{
	char	*line;
	int		fd;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		// exit (err_file(map_name));//to compile with errors.c
		exit (-3);//error file open failed
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		//
		//also it's neccessary check if there are NO, SU, WE, EA, C, and F before map
		//
		count_cols(data, line);
		(*data)->num_rows++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	replace_spaces(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == 32)
			(*str)[i] = '0';
		if ((*str)[i] == 'N' || (*str)[i] == 'S' || (*str)[i] == 'W' || (*str)[i] == 'E')
			(*str)[i] = '0';
		i++;
	}
}

void	parser(char *map_name, t_data *data)
{
	char	**tab;
	int		i;
	char 	*str;
	int		fd = 0;

	i = -1;
	check_map(&data, map_name);
	//DELETE
	printf("check! check_map\n");
	printf("data->row: %d\ndata->cols: %d\ndata->person: %d\n", data->num_rows, data->num_cols, data->num_person);
	// data->num_rows = count_rows(map_name);
	tab = (char **)ft_calloc(data->num_rows + 1, sizeof(char *));
	if (!tab)
		exit(0);//memory allocation error
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		printf("open failed\n");
		exit(-3);//error file open failed
	}
	str = get_next_line(fd);
	while (++i < data->num_rows)
	{
		tab[i] = ft_strdup(str);
		replace_spaces(&tab[i]);
		printf("%d: %s", i, tab[i]);
		free(str);
		str = get_next_line(fd);
	}

	t_point	size;

	size.x = data->num_cols;
	size.y = data->num_rows;

	printf("\ncheck result of flood fill!!\n");

	flood_fill(tab, size, data->pt_person);
	//DELETE
	for (int i = 0; tab[i]; i++)
		printf("%s", tab[i]);
}



int	main(int ac, char **av)
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
	if (check_file_format(av[1]) == -1)
		return (-2);//error incorrect file format 

	//check file
	// fd = open(av[1], O_RDONLY);
	// if (fd < 0)
	// {
	// 	printf("ajajajaaaaaaaa\n");
	// 	return (-3);//error file open failed
	// }
	parser(av[1], &data);
	printf("after parser\n");
	return (0);
}
