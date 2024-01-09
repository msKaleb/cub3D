#include "ft_cub3d.h"

/**
 * @brief check if the coming move is out of bounds or into a wall
  */
void	validate_pos_bonus(t_player *player, double next_x, double next_y)
{
	if (player->map[(int)next_y][(int)next_x] == 'F')
	{
		player->pos_x = next_x;
		player->pos_y = next_y;
	}
}