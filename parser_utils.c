/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:05:04 by nimai             #+#    #+#             */
/*   Updated: 2024/01/14 19:49:22 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"
#include <fcntl.h>
#include <stdio.h>

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
	int	j;

	i = 0;
	j = 0;
	while (map[data->map_size.y - 1 - i][0] == '\n')
		i++;
	if (map[j][0] == 32 || map[j][0] == 10)
		j++;
	if (ft_strchr(map[j], 'F') || ft_strchr(map[data->map_size.y - 1 - i], 'F') || ft_strchr(map[j], '2') || ft_strchr(map[data->map_size.y - 1 - i], '2'))
	{
		printf("the first or the last line\n");
		return (-1);
	}
	i = 0;
	while (map[i] && i < data->map_size.y)
	{
		// this line throws an 'Invalid read of size 1' valgrind error,
		// if ft_strlen(map[i]) is less than 2 (eg '\n'), tries to read at map[i][-1]
		// couldn't we skip lines with just a '\n' character?
		if (map[i][0] == 'F' || map[i][(int)ft_strlen(map[i]) - 2] == 'F' || map[i][0] == '2' || map[i][(int)ft_strlen(map[i]) - 2] == '2')
		{
			printf("the right or the left edge\n");
			return (-1);
		}
		i++;
	}
	return (1);
}
