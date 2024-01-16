/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:17:33 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/16 14:50:51 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	err_arg_number(void)
{
	printf("%sUsage: ./cub3D map.cub%s\n", GREEN, RESET);
	return (1);
}

int	err_file(char *file)
{
	printf("%sError\nCould not open the file:%s %s\n", RED, RESET, file);
	return (1);
}

int	err_mlx(t_mlx *m, char *msg)
{
	if (!msg)
		printf("%sError on minilbx%s\n", RED, RESET);
	else
		printf("%s%s%s\n", RED, msg, RESET);
	close_mlx(m);
	return (1);
}

int	err_map(void)
{
	printf("%sError\nFailed map loading%s\n", RED, RESET);
	return (1);
}

int	err_parse(char *msg)
{
	printf("%sError\n%s%s\n", RED, msg, RESET);
	return (-1);
}
