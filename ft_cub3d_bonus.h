#ifndef FT_CUB3D_BONUS_H
# define FT_CUB3D_BONUS_H

# include "libft/libft.h"
# include "colors.h"
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
# define DEFAULT_X 		800.0
# define DEFAULT_Y 		600.0
# define MOVE_SPEED		0.07
# define ROTATION_SPEED	0.03
# define MAX_TEXTURES	4

/* Events and values for mlx_hook */
# define ON_KEYDOWN			2
# define ON_KEYUP			3
# define ON_MOUSEDOWN		4
# define ON_MOUSEUP			5
# define ON_MOUSEMOVE		6
# define ON_EXPOSE			12
# define ON_DESTROY			17
# define X_KEYPRESS			1		// (1L << 0)
# define X_KEYRELEASE		2		// (1L << 1)
# define X_POINTERMOTION	64		// (1L << 6)
# define X_MASK				131072	// (1L << 17), for Linux

//minimap
# define BLOCKSIZE 3
# define PLAYERSIZE 6

typedef struct s_mlx	t_mlx;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

/**
* @brief obtain data in general (main structure)
* @param tex_path[0]: north
* @param tex_path[1]: south
* @param tex_path[2]: west
* @param tex_path[3]: east
*/
typedef struct s_data
{
	t_point	map_size;
	t_point	pt_person;

	int		num_person;
	int		pos_map;
	int		floor_col;
	int		ceiling_col;
	char	dir_person;
	char	*tex_path[4];
	char	**minimap;
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
 * @param side				orientation of wall (0 towards E-W / 1 towards N-S)
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
	int		floor_col;
	int		ceiling_col;
}				t_raycast;

typedef struct s_texture
{
	void	*texture;
	void	*text_addr;
	int		text_w;
	int		text_h;
	int		bpp;
	int		size_line;
	int		endian;
	int		text_x_coord;
	int		text_y_coord;
}				t_texture;
// the FOV is 2 * atan(0.66/1.0)=66°
typedef struct s_player
{
	t_texture	text[MAX_TEXTURES];
	t_data		*data;
	t_mlx		*m;

	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		width;
	double		height;

	int			motion_ns;
	int			motion_ew;
	int			motion_rot;

	char		dir;
	char		**map;
}				t_player;

typedef struct s_initial_dir
{
	double	orientation[4];
}				t_initial_dir;

/* minilibx structure */
typedef struct s_mlx
{
	t_texture	texture;
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

int		release_motion(int key_code, t_mlx *m);
int		set_motion(int key_code, t_mlx *m);
int		render_frame(t_mlx *m);
int		render_frame_bonus(t_mlx *m);
int		err_arg_number(void);
int		err_file(char *file);
int		close_mlx(t_mlx *m);
int		err_mlx(t_mlx *m);
int		is_space(char c);
int		err_map(void);

void	load_textures(t_texture *text, t_mlx *m, t_data *data);
void	init_player(t_player *player, t_data *data, t_mlx *m);
void	raycast(t_raycast *ray, t_player *player, t_mlx *m);
void	print_wall_line(t_mlx *m, t_texture *t, int x);
void	print_pixel(t_mlx *m, t_point p, int color);
void	print_line(t_raycast *ray, t_mlx *m, int x);
void	trim_non_ascii(char **tab, int rows);
void	free_map(t_player *player);
void	rotate_player(t_mlx *m);
// void	move_player(t_mlx *m);
void	init_mlx(t_mlx *m);
void	*free_2dimension(char **strs);//function name??

/**
 * @brief parser
  */
// char	**parser(char *map_name, t_data *data);
char	**parser_bonus(char *map_name, t_data *data);
int		check_file_format(char *str);

/**
 * @brief parser_utils
  */
int		is_brank(char *line);
void	replace_spaces(char **str);
int		is_overflow(char **map, t_data *data);

/**
 * @brief parser_check_map
  */
int		check_map(t_data **data, char *map_name);

/**
 * @brief parser_get_rgb
  */
int		get_rgb(char *str);

/**
 * @brief flood_fill
  */
void	flood_fill(char **tab, t_point size, t_point begin);

void	minimap(t_mlx *m, t_data *data);

void	draw_player(t_mlx *m, t_point i, char **minimap);


#endif /* FT_CUB3D_H */
