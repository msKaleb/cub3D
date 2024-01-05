#include "ft_cub3d.h"

/**
 * @brief load the textures from the .cub file
  */
void	load_textures(t_texture *text, t_mlx *m, t_data *data)
{
	char	*path;
	int		i;

	(void)data;
	i = -1;
	trim_non_ascii(data->tex_path, MAX_TEXTURES);
	while (++i < MAX_TEXTURES)
	{
		path = data->tex_path[i];
		text[i].texture = mlx_xpm_file_to_image(m->mlx, path,
				&text[i].text_w, &text[i].text_h);
		if (!text[i].texture)
			exit(printf("Error loading texture: %s\n", path));
		text[i].text_addr = mlx_get_data_addr(text[i].texture,
				&text[i].bpp, &text[i].size_line, &text[i].endian);
	}
}

void	texture_calculations(t_mlx *m, t_texture *t)
{
	double	wall_x_coord;
	int		text_x_coord;

	if (m->ray.side == 0)
		wall_x_coord = m->player.pos_y + m->ray.perp_wall_dist * m->ray.dir_y;
	else
		wall_x_coord = m->player.pos_x + m->ray.perp_wall_dist * m->ray.dir_x;
	wall_x_coord -= floor(wall_x_coord);
	text_x_coord = (int)(wall_x_coord * (double)(t->text_w));
	if ((m->ray.side == 0 && m->ray.dir_x > 0)
		|| (m->ray.side == 1 && m->ray.dir_y < 0))
		text_x_coord = t->text_w - text_x_coord - 1;
}
