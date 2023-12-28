/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:17:33 by msoria-j          #+#    #+#             */
/*   Updated: 2023/12/28 16:45:12 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	err_arg_number(void)
{
	printf("Usage: ./cub3D map.cub\n");
	return (1);
}

int	err_file(char *file)
{
	printf("Could not open the file: %s\n", file);
	return (1);
}
int	err_mlx(void)
{
	printf("Error on minilbx\n");
	return (1);
}
