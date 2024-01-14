#include "ft_cub3d_bonus.h"

/**
 * @brief free memory and destroy the mlx window
 * @note using MAX_TEXTURES for weapon free because uses the same amount
 * of images as textures array
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

/**
 * @brief initializes the mlx instance, 
 * firstly to NULL to avoid potential double frees
  */
void	init_mlx_bonus(t_mlx *m)
{
	int	i;
	
	i = -1;
	while (++i < MAX_TEXTURES)
	{
		m->player.text[i].texture = NULL;
		m->player.weapon[i].img = NULL;
	}
	m->mlx = NULL;
	m->win = NULL;
	m->img = NULL;
	m->mlx = mlx_init();
	if (m->mlx != NULL)
		m->win = mlx_new_window(m->mlx, DEFAULT_X, DEFAULT_Y, \
		"cub3D Project - nimai & msoria-j");
	if (m->win != NULL)
		m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	if (m->img == NULL)
		exit(err_mlx_bonus(m));
	m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->endian);
	m->cur.x = DEFAULT_X / 2;
	m->cur.y = DEFAULT_Y / 2;
	mlx_mouse_move(m->mlx, m->win, m->cur.x, m->cur.y);
	mlx_mouse_hide(m->mlx, m->win);
}

/**
 * @brief set of events on key press
  */
int	set_motion_bonus(int key_code, t_mlx *m)
{
	if (key_code == XK_ESCAPE)
		close_mlx_bonus(m);
	if (key_code == XK_W)
		m->player.motion_ns = 1;
	else if (key_code == XK_S)
		m->player.motion_ns = -1;
	else if (key_code == XK_A)
		m->player.motion_ew = 1;
	else if (key_code == XK_D)
		m->player.motion_ew = -1;
	else if (key_code == XK_LEFT)
		m->player.motion_rot = -1;
	else if (key_code == XK_RIGHT)
		m->player.motion_rot = 1;
	else if (key_code == XK_UP)
		m->player.shot_flag = 1;
	render_frame_bonus(m);
	return (0);
}

/**
 * @brief set of events on key release
  */
int	release_motion_bonus(int key_code, t_mlx *m)
{
	char	*current;
	char	*to_check;

	current = &m->player.map[(int)m->player.pos_y][(int)m->player.pos_x];
	if (key_code == XK_W)
		m->player.motion_ns = 0;
	else if (key_code == XK_S)
		m->player.motion_ns = 0;
	else if (key_code == XK_A)
		m->player.motion_ew = 0;
	else if (key_code == XK_D)
		m->player.motion_ew = 0;
	else if (key_code == XK_LEFT)
		m->player.motion_rot = 0;
	else if (key_code == XK_RIGHT)
		m->player.motion_rot = 0;
	else if (key_code == XK_SPACE)
	{
		to_check = get_type(m);
		if (*to_check == '2')
			*to_check = 'D';
		else if (*to_check == 'D' && current != to_check)
			*to_check = '2';
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_mlx *m)
{
	(void)x;
	(void)y;
	if (button == 1)
		m->player.shot_flag = 1;
	return (0);
}
