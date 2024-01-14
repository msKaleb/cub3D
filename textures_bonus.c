#include "ft_cub3d_bonus.h"

/**
 * @brief load the textures from the .cub file
 * @note trim_non_ascii from 0 to MAX_TEXTURES - 1 to avoid crash, 
 * the last texture is for the door and it is not in the array
 * @todo use strdup in path??
  */
void	load_textures_bonus(t_texture *text, t_mlx *m, t_data *data)
{
	char	*path;
	int		i;

	i = -1;
	trim_non_ascii(data->tex_path, MAX_TEXTURES - 1);
	while (++i < MAX_TEXTURES)
	{
		path = data->tex_path[i];
		if (i == 4)
			path = "textures/door.xpm"; // strdup??
		text[i].texture = mlx_xpm_file_to_image(m->mlx, path,
				&text[i].text_w, &text[i].text_h);
		if (!text[i].texture)
			exit(printf("Error loading texture: %s\n", path));
		text[i].text_addr = mlx_get_data_addr(text[i].texture,		// manage error
				&text[i].bpp, &text[i].size_line, &text[i].endian);
	}
}
