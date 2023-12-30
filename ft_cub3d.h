/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:25:59 by msoria-j          #+#    #+#             */
/*   Updated: 2023/12/30 06:56:07 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_CUB3D_H
# define _FT_CUB3D_H

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
# define DEFAULT_X 		640
# define DEFAULT_Y 		480

/* Events and values for mlx_hook */
# define ON_KEYDOWN		2
# define ON_KEYUP		3
# define ON_MOUSEDOWN	4
# define ON_MOUSEUP		5
# define ON_MOUSEMOVE	6
# define ON_EXPOSE		12
# define ON_DESTROY		17
# define X_MASK			131072 // (1L << 17), for Linux

/* minilibx structure */
typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			bpp;
	int			sl;
	int			endian;
}				t_mlx;

typedef struct	s_point
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
}	t_data;

// the FOV is 2 * atan(0.66/1.0)=66°
typedef struct s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}				t_player;

/* Functions prototipes */
int		err_arg_number(void);
int		err_file(char *file);
int		err_mlx(void);
int		key_hook(int key_code, t_mlx *m);
int		close_mlx(t_mlx *m);

void	print_pixel(t_mlx *m, t_point p, int color);
void	init_mlx(t_mlx *m);

void	*free_2dimension(char **strs);//function name??

/**
 * @brief parser
  */
char	**parser(char *map_name, t_data *data);

/**
 * @brief flood_fill
  */
void	flood_fill(char **tab, t_point size, t_point begin);

#endif /* _FT_CUB3D_H */
