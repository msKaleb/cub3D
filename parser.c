/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:05:04 by nimai             #+#    #+#             */
/*   Updated: 2023/12/28 17:08:34 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_cub3d.h"
#include <fcntl.h>
#include <stdio.h>

#include "libft/libft.h"//for test

/**
* @brief obtain data in general (main structure)
*/
typedef struct s_data
{
	int	num_rows;
	int	num_person;
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

int	count_rows(char *map_name)
{
	char	*line;
	int		ret;
	int		fd;


	//check file
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		printf("ajajajaaaaaaaa\n");
		return (-3);//error file open failed
	}
	ret = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		ret++;
		line = get_next_line(fd);
	}
	close(fd);
	return (ret);
}

void	parser(char *map_name, t_data *data)
{
	char	**tab;
	int		i;

	i = -1;
	data->num_rows = count_rows(map_name);
	tab = (char **)ft_calloc(data->num_rows + 1, sizeof(char *));
	if (!tab)
		exit(0);//memory allocation error
	char *str;
	int	fd = 0;
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		printf("open failed\n");
		exit(-3);//error file open failed
	}
	str = get_next_line(fd);
	while (++i < data->num_rows)
	{
		printf("%d: %s", i, str);
		free(str);
		str = get_next_line(fd);
	}
}



int	main(int ac, char **av)
{
	t_data	data;
	int		fd;

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
