#include "ft_cub3d_bonus.h"

int	err_mlx_bonus(t_mlx *m)
{
	printf("%sError on minilbx%s\n", RED, RESET);
	close_mlx_bonus(m);
	return (1);
}