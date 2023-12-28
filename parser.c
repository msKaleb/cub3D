/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:05:04 by nimai             #+#    #+#             */
/*   Updated: 2023/12/28 16:18:06 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"
#include <fcntl.h>

int	check_file_format(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strcmp(".cub", str + (len - 4)))
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	int	fd;

	fd = 0;
	if (ac != 2)
		return (-1);//error bad argument
	//check format;
	if (check_file_format(av[1]) == -1)
		return (-2);//error incorrect file format 

	//check file
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (-3);//error file open failed
	parser(fd);
	return (0);
}
