#include "ft_cub3d.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || (c > 8 && c < 14))
		return (1);
	else
		return (0);
}

void	trim_non_ascii(char **tab, int rows)
{
	char	*tmp;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	k = 0;
	while (++i < rows)
	{
		tmp = ft_calloc(1, ft_strlen(tab[i]));
		while (++j < (int)ft_strlen(tab[i]))
		{
			if (!ft_isspace(tab[i][j]))
				tmp[k++] = tab[i][j];
		}
		free(tab[i]);
		tab[i] = tmp;
		j = -1;
		k = 0;
		/* tmp = ft_strtrim(tab[i], "\n");
		free(tab[i]);
		tab[i] = tmp; */
	}
}

void	free_map(t_player *player)
{
	int	i;
	int	rows;

	i = 0;
	rows = (int)player->height;
	while (i < rows)
	{
		free(player->map[i]);
		i++;
	}
	free(player->map);
}
