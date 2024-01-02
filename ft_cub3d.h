/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:25:59 by msoria-j          #+#    #+#             */
/*   Updated: 2024/01/02 18:48:33 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# include "libft/libft.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>

/* Keys may vary depending on the OS */
# ifdef __linux__
#  include "minilibx_linux/mlx.h"	// MLX for Linux
#  define XK_ESCAPE 	0xff1b
#  define XK_W 			0x77
#  define XK_A 			0x61
#  define XK_S 			0x73
#  define XK_D 			0x64
#  define XK_Q 			0x71
#  define XK_E 			0x65
#  define XK_P 			0x70
#  define XK_UP			0xff52
#  define XK_DOWN		0xff54
#  define XK_LEFT		0xff51
#  define XK_RIGHT		0xff53
# elif __APPLE__
#  include "minilibx_opengl/mlx.h"			// MLX for Mac
#  define XK_ESCAPE 	0x35
#  define XK_W 			0x0d
#  define XK_A 			0x00
#  define XK_S 			0x01
#  define XK_D 			0x02
#  define XK_Q 			0x0c
#  define XK_E 			0x0e
#  define XK_P 			0x23
#  define XK_UP			0x7e
#  define XK_DOWN		0x7d
#  define XK_LEFT		0x7b
#  define XK_RIGHT		0x7c
# endif /* OS Check */

/* Not defined in my distro */
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

/* Some needed values */
# define DEFAULT_COLOR 	0xBADA55	// Badass color
# define DEFAULT_SKY	0x87CEEB
# define DEFAULT_FLOOR	0x92745B
# define DEFAULT_X 		640.0
# define DEFAULT_Y 		480.0
# define MOVE_SPEED		0.2
# define ROTATION_SPEED	0.15

/* Events and values for mlx_hook */
# define ON_KEYDOWN		2
# define ON_KEYUP		3
# define ON_MOUSEDOWN	4
# define ON_MOUSEUP		5
# define ON_MOUSEMOVE	6
# define ON_EXPOSE		12
# define ON_DESTROY		17
# define X_MASK			131072 // (1L << 17), for Linux


typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

/**
* @brief obtain data in general (main structure)
*/
typedef struct s_data
{
	int		num_rows;
	int		num_cols;
	int		num_person;
	t_point	pt_person;
}				t_data;

/**
 * @brief raycast structure
 * @param cam_x 			x coordinate on the camera plane
 * @param dir_x/dir_y		ray direction vector
 * @param delta_x/delta_y	distance vector
 * @param side_x/side_y		distance in grid x/y
 * @param perp_wall_dist	perpendicular distance from camera plane to the wall
 * @param map_x/map_y		square of the grid the ray is in
 * @param step_x/step_y		positive or negative direction
 * @param line_height		the vertical lines which will form the 3d image
 * @param is_wall			checks if the ray hit a wall
 * @param side				type of wall (NS or EW)
 */
typedef struct s_raycast
{
	double	cam_x;
	double	dir_x;
	double	dir_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	double	perp_wall_dist;

	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		line_height;
	int		is_wall;
	int		side;
	int		line_first_px;
	int		line_last_px;
}				t_raycast;

// the FOV is 2 * atan(0.66/1.0)=66°
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

	char	dir;
	char	**map;	// maybe put it in another struct
}				t_player;

typedef struct s_initial_dir
{
	double	orientation[4];
}				t_initial_dir;

/* minilibx structure */
typedef struct s_mlx
{
	t_player	player;
	t_raycast	ray;

	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;

	int			bpp;
	int			sl;
	int			endian;
}				t_mlx;

/* Functions prototipes */
int		err_arg_number(void);
int		err_file(char *file);
int		err_mlx(void);
int		key_hook(int key_code, t_mlx *m);
int		close_mlx(t_mlx *m);

void	print_pixel(t_mlx *m, t_point p, int color);
void	init_mlx(t_mlx *m);
void	raycast(t_raycast *ray, t_player *player, t_mlx *m);
void	print_line(t_raycast *ray, t_mlx *m, int x);

void	init_player(t_player *player);
void	move_player(t_mlx *m, int key_code);
void	rotate_player(t_mlx *m, int key_code);
int		has_to_move(int key_code);

void	*free_2dimension(char **strs);//function name??

/**
 * @brief parser
  */
char	**parser(char *map_name, t_data *data);

/**
 * @brief flood_fill
  */
void	flood_fill(char **tab, t_point size, t_point begin);

#endif /* FT_CUB3D_H */
