/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 00:10:33 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/14 00:11:58 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d_bonus.h"

/**
 * @brief a replace for mlx_put_image_to_window(), because
 * it does not manage transparency in linux
  */
void	print_image(t_mlx *m, t_sprite *img, int x, int y)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			color = *(unsigned int *)
				(img->addr + (j * img->size_line) + (i * img->bpp_div));
			if (color >= 0)
				print_pixel(m, (t_point){i + x, j + y}, color);
			j++;
		}
		i++;
	}
}

/**
 * @brief render the sprite of the weapon
 * @note MAC version
  */
/* void	render_weapon(t_mlx *m, t_sprite *weapon, int *frame)
{
	int	x;
	int	y;

	if (*frame == 50)
	{
		*frame = 1;
		m->player.shot_flag = 0;
	}
	x = DEFAULT_X / 2 - weapon[0].width / 2;
	y = DEFAULT_Y - weapon[0].height;
	mlx_put_image_to_window(m->mlx, m->win, weapon[*frame / 10].img,x, y);
	if (m->player.shot_flag == 1)
		*frame += 1;
} */

/**
 * @brief render the sprite of the weapon
 * @note Linux version
  */
void	render_weapon(t_mlx *m, t_sprite *weapon, int *frame)
{
	int	x;
	int	y;

	if (*frame == 50)
	{
		*frame = 1;
		m->player.shot_flag = 0;
	}
	x = DEFAULT_X / 2 - weapon[0].width / 2;
	y = DEFAULT_Y - weapon[0].height;
	print_image(m, &weapon[*frame / 10], x, y);
	if (m->player.shot_flag == 1)
		*frame += 1;
}

void	load_weapon(t_mlx *m, t_sprite *weapon)
{
	char	**gun;
	int		i;

	gun = (char *[5]){"sprites/pistol/pistol1.xpm",
		"sprites/pistol/pistol2.xpm",
		"sprites/pistol/pistol3.xpm",
		"sprites/pistol/pistol4.xpm",
		"sprites/pistol/pistol5.xpm"};
	i = 0;
	while (i < 5)
	{
		weapon[i].img = mlx_xpm_file_to_image(m->mlx, gun[i],
				&weapon[i].width, &weapon[i].height);
		weapon[i].addr = mlx_get_data_addr(weapon[i].img, &weapon[i].bpp,
				&weapon[i].size_line, &weapon[i].endian);
		weapon[i].bpp_div = weapon[i].bpp / 8;
		i++;
	}
}

/**
 * @brief refreshes the frame and applies character movement
  */
int	render_frame_bonus(t_mlx *m)
{
	move_player_bonus(m);
	rotate_player(m);
	mlx_destroy_image(m->mlx, m->img);
	m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	raycast(&m->ray, &m->player, m);
	minimap(m, m->player.data);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
	render_weapon(m, m->player.weapon, &m->player.wframe);
	return (0);
}
