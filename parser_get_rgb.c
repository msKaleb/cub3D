/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_rgb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:15:59 by nimai             #+#    #+#             */
/*   Updated: 2024/01/10 12:04:21 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"
#include "colors.h"
#include <fcntl.h>
#include <stdio.h>

static int	separate_rgb(char *str, int pos[3], int colour[3])
{
	char	*tmp;

	while (str[pos[0]] && str[pos[0]] == 32)
		pos[0]++;
	if (!ft_isdigit(str[pos[0]]))
		return (printf("colour is not digit\n"), -1);//error
	pos[1] = pos[0];
	while (str[pos[1]] && ft_isdigit(str[pos[1]])/* str[pos[1]] != 32, str[pos[1]] != ',' */)
		pos[1]++;
	if (((str[pos[1]]) && str[pos[1]] != 32 && str[pos[1]] != 10) || (pos[2] != 2 && str[pos[1]] != ','))
		return (printf("colour has incorrect letter\n"), -1);
	tmp = ft_substr(str, pos[0], pos[1] - pos[0]);
	colour[pos[2]] = ft_atoi(tmp);
	free (tmp);
	if (colour[pos[2]] < 0 || colour[pos[2]] > 255)
		return (printf("colour is out of range\n"), -1);//error
	pos[2]++;
	pos[0] = pos[1] + 1;
	return (0);
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
	int		ret;

	ft_bzero(pos, sizeof(int) * 3);
	ft_bzero(colour, sizeof(int) * 3);
	while (str[pos[0]] && pos[2] < 3)
	{
		if (separate_rgb(str, pos, colour) == -1)
			return (-1);
	}
	if (pos[2] < 3)
		return (printf("lack of information for colour\n"), -1);//error OR we can put 0 instead of return error
	if (is_brank(&str[pos[0]]) == 0)
		return (printf("I have more than I should have\n"), -1);//error OR we can put 0 instead of return error
	ret = (colour[0] << 16) + (colour[1] << 8) + (colour[2]);
	return (ret);
}
