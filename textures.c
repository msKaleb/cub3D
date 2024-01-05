#include "ft_cub3d.h"

/* static */ int	darken_color(int color)
{
	return ((color / 2) << 16) + ((color / 2) << 8) + (color / 2);
}

static int	get_text_x_coord(t_mlx *m, int width)
{
	double	wall_x_coord;
	int		text_x_coord;

	if (m->ray.side == 0)
		wall_x_coord = m->player.pos_y + m->ray.perp_wall_dist * m->ray.dir_y;
	else
		wall_x_coord = m->player.pos_x + m->ray.perp_wall_dist * m->ray.dir_x;
	wall_x_coord -= floor(wall_x_coord);
	text_x_coord = (int)(wall_x_coord * (double)(width));
	if ((m->ray.side == 0 && m->ray.dir_x > 0)
		|| (m->ray.side == 1 && m->ray.dir_y < 0))
		text_x_coord = width - text_x_coord - 1;
	return (text_x_coord);
}

void	get_texel_color(t_mlx *m, t_texture *t, int x)
{
	double	step;
	double	text_pos;
	int		color;
	int		y;

	t->text_x_coord = get_text_x_coord(m, t->text_w);
	step = 1.0 * t->text_h / m->ray.line_height;
	// step = (double)(t->text_h / m->ray.line_height); ??
	text_pos = (m->ray.line_first_px - DEFAULT_Y / 2 + m->ray.line_height / 2) * step;
	y = m->ray.line_first_px - 1;
	while (y < m->ray.line_last_px)
	{
		t->text_y_coord = (int)text_pos & (t->text_h - 1);
		text_pos += step;
		// color = xpm[t->text_h * t->text_y_coord + t->text_x_coord]; // get the color from the texture
		color = 8224125; // just for debugging purposes
		/* if (m->ray.side == 1)
			color = darken_color(color); */
		print_pixel(m, (t_point){x, y++}, color);
	}
}

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
