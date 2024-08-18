/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 00:04:54 by marvin            #+#    #+#             */
/*   Updated: 2024/07/27 00:04:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include <stdbool.h>
# include "get_next_line/get_next_line.h"

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080
#define MOVE_SPEED 0.05
#define ROT_SPEED 0.05
#define TEXTURE_SIZE 64
#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

# define TILE_SIZE 8
# define FOV 60 * (M_PI / 180)
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05

#define PI 3.1415926535
#define PI_DOUBLE 6.2831853071
#define PI_HALF 1.5707963267
#define PI_THREE_HALFS 4.7123889803

#define GRID_LEN 64
// for parsing 
typedef enum s_identifier
{
	N,
	S,
	E,
	W,
	F,
	C
} t_identifier;


typedef struct s_raycasting
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	size_t		map_x;
	size_t map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
}	t_raycasting;

typedef struct s_player
{
	double			player_x;
	double			player_y;
	double			player_dir_x;
	double			player_dir_y;
	double			plane_x;
	double			plane_y;
}	t_player;

typedef struct s_textures
{
	int *image_texture_data;
	int width;
	int height;
	int bpp;
	int size_line;
	int endian;
	int y;
	int tex_x;
	double pos;
	double step;
	double wall_x;
	int draw_start;
	int draw_end;

} t_textures;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				*img_data;
	// parsing
	char			**map;
	int				fd;
	char			*no;
	char			*so;
	char *we;
	char *ea;
	char *line;
	char *line_tmp;
	size_t map_columns;
	size_t map_rows;
	int ceiling_color;
	int floor_color;
	int hero;
	char hero_orientation; // N S E OR W
	size_t row_start_position; // i
	size_t col_start_position; // j
	float pos_angle;
	int *texture_buffer[4];
	int bpp;
	int				endian;
	int				size_line;
	t_raycasting	*rays;
	t_player		player;
	t_textures texture;
}	t_data;


//fonctions
void init_map(t_data *data);
void init_mlx(t_data *data);
void init_player(t_data *data);
int handle_keypress(int keycode, t_data *data);
void draw_game(t_data *data, int x);
void cast_rays(t_data *data, int x);
void init_textures(t_data *data);
void free_all(t_data *data);

// parsing
int error_msg(t_data *game, char *mess, int num);
bool check_args(int argc, const char **argv);
bool is_already_loaded(t_data *game, t_identifier elem);
int is_xpm(char *path);
void get_color_code(t_identifier color, char *line, t_data *game);
void get_path_to_texture(t_identifier direction, char *line, t_data *game);
void parse_file(t_data *game, const char *file);
int is_space(char c);
bool is_empty_line(char *line);
void process_map(t_data *game, const char *file);
bool is_valid_char(t_data *game, char c);
bool is_all_set(t_data *game);
void free_map(t_data *game);
void clean_up(t_data *game);
void fill_map(t_data *game, char *line);

// init
//void init_mlx(t_data *data);
int close_window(t_data *game);
void init_player(t_data *data);
void init_hero_pos(t_data *game);
void init_game_input(t_data *game);
void init_graphics(t_data *game);
void clean_mlx(t_data *game);

#endif