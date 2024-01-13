/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:05:04 by nimai             #+#    #+#             */
/*   Updated: 2024/01/13 10:15:35 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	*free_2dimension(char **strs)//function name??
{
	int	i;

	i = -1;
	while (strs && strs[++i])
	{
		free(strs[i]);
		strs[i] = NULL;
	}
	free(strs);
	return (NULL);
}

void	*free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free (data->tex_path[i]);
		data->tex_path[i] = NULL;
		i++;
	}
	return (NULL);
}
