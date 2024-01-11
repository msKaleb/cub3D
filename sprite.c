#include "ft_cub3d_bonus.h"

void	print_sprite(t_mlx *m, t_texture *t)
{
	t_point	start;
	t_point	pos;

	pos.x = 0;
	while (pos.x < 64)
	{
		pos.y = 0;
		while (pos.y < 64)
		{
			t[index].text_y_coord = (int)text_pos & (t[index].text_h - 1);
		text_pos += step;
		color = ((int *)t[index].text_addr) \
			[t[index].text_h * t[index].text_y_coord + t[index].text_x_coord];
		if (m->ray.side == 0)
			color = darken_color(color);
		print_pixel(m, (t_point){x, y++}, color);
		}

	}
}


void	sprite(t_mlx *m, t_data *data)
{
	int	i;

	i = 0;
    // (void)m;
    // printf("Line: %d / %s\n", __LINE__, __FILE__);
	// count first how many sprite I have, and draw them until the last one
	while (i < data->num_sprite)
	{
		print_sprite(m, m->player.text);
		i++;
	}
	printf("I drew %d sprites!\n", data->num_sprite);
}