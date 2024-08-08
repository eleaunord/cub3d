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

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define TILE_SIZE 8
# define FOV 60 * (M_PI / 180)

typedef struct s_raycasting
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
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

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				*img_data;
	char			**map;
	int				bpp;
	int				ceiling_color;
	int				floor_color;
	int				endian;
	int				size_line;
	double			player_x;
	double			player_y;
	double			player_dir_x;
	double			player_dir_y;
	double			plane_x;
	double			plane_y;
	t_raycasting	*rays;
}	t_data;

//fonctions
void	init_map(t_data *data);
void	init_mlx(t_data *data);
void	render_minimap(t_data *data);
void	init_player(t_data *data);

void	cast_rays(t_data *data, int x);

#endif