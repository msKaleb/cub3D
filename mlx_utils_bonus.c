#include "ft_cub3d_bonus.h"

/**
 * @brief free memory and destroy the mlx window
 * @note using MAX_TEXTURES for weapon free because uses the same amount
 * of images as textures array
 * @todo free minimap, but in mandatory there is no minimap.
  */
int	close_mlx_bonus(t_mlx *m)
{
	int	i;

	i = -1;
	while (++i < MAX_TEXTURES)
	{
		if (m->player.text[i].texture)
			mlx_destroy_image(m->mlx, m->player.text[i].texture);
		if (m->player.weapon[i].img)
			mlx_destroy_image(m->mlx, m->player.weapon[i].img);
	}
	free_2dimension(m->player.map);
	free_2dimension(m->player.data->minimap);
	free_data(m->player.data);
	if (m->mlx && m->img)
		mlx_destroy_image(m->mlx, m->img);
	if (m->win)
		mlx_destroy_window(m->mlx, m->win);
	free(m->mlx);
	exit(EXIT_SUCCESS);
}
