/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:05:04 by nimai             #+#    #+#             */
/*   Updated: 2023/12/29 13:32:09 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "ft_cub3d.h"
#include <fcntl.h>
#include <stdio.h>
#include "colors.h"

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


size_t	ft_stroverwrite(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;

	(void)dstsize;
	printf("overwriting\n");
	printf("%s\n\n", dst);
	// printf("%s\n%s", dst, src);
	
	srclen = ft_strlen(src);
	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < srclen - 1)
		{
			dst[i] = src[i];
			i++;
		}
		// dst[i] = '\0';
	}
	return (srclen);
}

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
		printf("%s", line);
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
	printf("replace: \n%s", *str);
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
	printf("last line: %s", map[data->num_rows - 2]);
	if (ft_strchr(map[0], 'F') || ft_strchr(map[data->num_rows - 2], 'F'))
	{
		printf("the first or last\n");
		return (-1);
	}
	//check each line the first letter and the last
	while (map[i] && i < data->num_rows)
	{
		printf("\nCHECK!");
		printf("map[%d][0]: %c\nmap[%d][ft_strlen(map[%d]) - 1]: %c\n", i, map[i][0], i, i, map[i][ft_strlen(map[i]) - 1]);
		printf("map[%d][data->num_cols - 1]: %c\n", i, map[i][data->num_cols - 1]);

		if (map[i][0] == 'F')
		{
			printf("the first letter: %c\n", map[i][0]);
			return (-1);
		}
		if (map[i][ft_strlen(map[i]) - 1] == 'F' || map[i][data->num_cols - 1] == 'F')
		{
			printf("the last letter: %c\n", map[i][ft_strlen(map[i])]);
			return (-1);
		}
		i++;
	}
	return (1);
}

char	**parser(char *map_name, t_data *data)
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


	// If you want to fill with 0 the map, these lines//
	/**
		231229 it's not working
	
	  */

	// tab = (char **)malloc((data->num_rows + 1) * sizeof(char *));
	// if (!tab)
	// 	exit(0);
	// // printf("Line: %d tab: %p\n", __LINE__, tab);
	// int	j = -1;
	// while (++j < data->num_rows)
	// {
	// 	tab[j] = (char *)malloc((data->num_cols + 1) * sizeof(char));
	// 	if (!tab[j])
	// 		exit(0);//memory allocation error
	// 	// printf("Line: %d tab[j]: %p\n", __LINE__, tab[j]);
	// 	tab[j] = ft_memset(tab[j], '0', data->num_cols - 1);
	// 	// if (j != data->num_rows -1)
	// 	tab[j][data->num_cols - 1] = '\n';
	// 	printf("%s \nlast one %d\ndata->cols %d\n", tab[j], tab[j][data->num_cols - 1], data->num_cols);

	// }

	// for (int i = 0; tab[i]; i++)
	// 	printf("%s", tab[i]);


	// If you want to fill with 0 the map, these lines//

	
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		printf("open failed\n");
		exit(-3);//error file open failed
	}
	// printf("Line: %d tab: %p\n", __LINE__, tab);
	str = get_next_line(fd);
	printf("%s\ncheck result of replace spaces!!%s\n", BLUE, RESET);
	while (++i < data->num_rows)
	{
		tab[i] = ft_strdup(str);
		replace_spaces(&tab[i]);
		printf("%s", tab[i]);
		free(str);
		str = get_next_line(fd);
	}
	
	// If you want to fill with 0 the map, these lines//
	/**
		231229 it's not working
	
	*/
	// i = -1;
	// while (++i < data->num_rows)
	// {
	// 	printf("\n%d line \n", i);

	// 	// tab[i] = ft_strdup(str);
	// 	// ft_strlcpy(tab[i], str, ft_strlen(str));
	// 	ft_stroverwrite(tab[i], str, ft_strlen(str));
	// 	printf("%s", tab[i]);
	// 	printf("%s", str);
	// 	printf("\n\n\n");
	// 	replace_spaces(&tab[i]);
	// 	printf("%s", tab[i]);
	// 	free(str);
	// 	str = get_next_line(fd);
	// }



	// If you want to fill with 0 the map, these lines//

	t_point	size;

	size.x = data->num_cols;
	size.y = data->num_rows;

	printf("\ncheck result of flood fill!!\n");

	flood_fill(tab, size, data->pt_person);
	if (is_overflow(tab, data) == -1)
	{
		//free memory
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

	//check file
	// fd = open(av[1], O_RDONLY);
	// if (fd < 0)
	// {
	// 	printf("ajajajaaaaaaaa\n");
	// 	return (-3);//error file open failed
	// }
	// parser(argv[1], &data);
	printf("after parser\n");
		/* parser */
	char	**map;
	map = parser(argv[1], &data);
	if (!map)
		return(1);//
	for (int i = 0; map[i]; i++)
		printf("%s", map[i]);
	/*  */
	return (0);
}
