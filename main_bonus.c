/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:23:06 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/13 13:54:17 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d_bonus.h"

void	init_raycast(t_raycast *ray, t_data *data)
{
	ray->cam_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->delta_x = 0;
	ray->delta_y = 0;
	ray->side_x = 0;
	ray->side_y = 0;
	ray->perp_wall_dist = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->line_height = 0;
	ray->is_wall = 0;
	ray->side = 0;
	ray->ceiling_col = data->ceiling_col;
	ray->floor_col = data->floor_col;
}

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

void	load_weapon(t_mlx *m, t_sprite *weapon)
{
	char	**gun;
	// int		x;
	// int		y;
	int		i;

	gun = (char*[5]){"sprites/pistol/pistol1.xpm",
		"sprites/pistol/pistol2.xpm",
		"sprites/pistol/pistol3.xpm",
		"sprites/pistol/pistol4.xpm",
		"sprites/pistol/pistol5.xpm"};
	i = 0;
	while (i < 5)
	{
		weapon[i].img = mlx_xpm_file_to_image(m->mlx, gun[i], &weapon[i].width, &weapon[i].height);
		weapon[i].addr = mlx_get_data_addr(weapon[i].img, &weapon[i].bpp, &weapon[i].size_line, &weapon[i].endian);
		weapon[i].bpp_div = weapon[i].bpp / 8;
		i++;
	}
	/* x = DEFAULT_X / 2 - weapon[0].width / 2;
	y = DEFAULT_Y - weapon[0].height;
	mlx_put_image_to_window(m->mlx, m->win, weapon[0].img,x, y);
	mlx_hook(m->win, ON_DESTROY, X_MASK, &close_mlx, &m);
	mlx_loop(m->mlx); */
}

int	mouse_hook(int button, int x, int y, t_mlx *m)
{
	(void)x;
	(void)y;

	if (button == 1)
		m->player.shot_flag = 1;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_mlx		m;

	if (argc < 2)
		return (err_arg_number());
	if (check_file_format(argv[1]) == -1)
		return (err_arg_number());//error incorrect file format 
	m.player.map = parser_bonus(argv[1], &data);
	if (!m.player.map)
	{
		free_data(&data);
		return (printf("Failed map loading\n"), 1);
	}
	// for(int i = 0; m.player.map[i]; i++)
	// {
	// 	printf("%s", m.player.map[i]);
	// }
	// printf("\n\nfinish write map to render\n");
	// for(int i = 0; data.minimap[i]; i++)
	// {
	// 	printf("%s", data.minimap[i]);
	// }
	// printf("\n\nfinish write map to minimap\n");
	// exit(0);
	init_mlx(&m);
	m.cur.x = DEFAULT_X / 2;
	m.cur.y = DEFAULT_Y / 2;
	mlx_mouse_move(m.win, DEFAULT_X / 2, DEFAULT_Y / 2); // MAC version
	// mlx_mouse_move(m.mlx, m.win, DEFAULT_X / 2, DEFAULT_Y / 2); // Linux version
	mlx_mouse_hide(m.mlx, m.win);
	// printf("Line: %d / %s\n", __LINE__, __FILE__);
	init_raycast(&m.ray, &data);
	m.player.dir = data.dir_person;
	init_player(&m.player, &data, &m);
	load_weapon(&m, &m.player.weapon[0]);
	// printf("Line: %d / %s\n", __LINE__, __FILE__);
	raycast(&m.ray, &m.player, &m);
	// mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
	mlx_mouse_hook(m.win, mouse_hook, &m);
	mlx_hook(m.win, ON_KEYDOWN, X_KEYPRESS, &set_motion_bonus, &m);
	mlx_hook(m.win, ON_KEYUP, X_KEYRELEASE, &release_motion_bonus, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx, &m);
	mlx_hook(m.win, ON_MOUSEMOVE, X_POINTERMOTION, &mouse_rotation_bonus, &m);

	mlx_loop_hook(m.mlx, &render_frame_bonus, &m);
	mlx_loop(m.mlx);
	free_2dimension(m.player.map);
	free_2dimension(data.minimap);
	free_data(&data);
	return(0);
}
