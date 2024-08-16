/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:27:58 by marvin            #+#    #+#             */
/*   Updated: 2024/07/30 13:27:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_game_input(t_data *game)
{
	game->we = NULL;
	game->ea = NULL;
	game->so = NULL;
	game->line = NULL;
	game->line_tmp = NULL;
	game->ceiling_color = -1;
	game->floor_color = -1;
	game->map_columns = 0;
	game->map_rows = 0;
	game->fd = 0;
	game->hero = 0;
	game->hero_orientation = 'H';
	game->row_start_position = 0;
	game->col_start_position = 0;
}
static void set_hero_orientation(t_data *game, char c)
{
	if (c == 'N')
	{
		game->hero_orientation = 'N';
		game->pos_angle = PI_HALF;
	}
	else if (c == 'S')
	{
		game->hero_orientation = 'S';
		game->pos_angle = PI_THREE_HALFS;
	}
	else if (c == 'E')
	{
		game->hero_orientation = 'E';
		game->pos_angle = 0;
	}
	else if (c == 'W')
	{
		game->hero_orientation = 'W';
		game->pos_angle = PI;
	}
}

void init_hero_pos(t_data *game)
{
	size_t i;
	size_t j;

	i = -1;
	while (++i < game->map_rows)
	{
		j = -1;
		while (++j < game->map_columns)
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
				game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				set_hero_orientation(game, game->map[i][j]);
				game->row_start_position = (float)i * GRID_LEN + GRID_LEN / 2;
				game->col_start_position = (float)j * GRID_LEN + GRID_LEN / 2;
				return;
			}
		}
	}
	error_msg(game, "Hero not found in map.\n", EXIT_FAILURE);
}

void	init_player(t_data *data)
{
	data->player.player_dir_x = cos(data->pos_angle) * 2.2;
	data->player.player_dir_y = sin(data->pos_angle) * -2.2; // 2.2 is the player's speed
	data->player.plane_x = 0;
	data->player.plane_y = 0.66;
}

void init_graphics(t_data *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		error_msg(game, "Error initializing mlx\n", EXIT_FAILURE);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_WIDTH, WIN_WIDTH, "Cub3D");
	if (!game->win_ptr)
		error_msg(game, "Error creating window\n", EXIT_FAILURE);
	game->img_ptr = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_WIDTH);
	if (!game->img_ptr)
		error_msg(game, "Error on mlx new image\n", EXIT_FAILURE);
	game->img_data = (int *)mlx_get_data_addr(game->img_ptr, &game->bpp,
											  &game->size_line, &game->endian);
	if (!game->img_data)
		error_msg(game, "Error on mlx get data addr\n", EXIT_FAILURE);
	game->rays = malloc(sizeof(t_raycasting));
	game->ceiling_color = 0x87CEEB;
	game->floor_color = 0x8B4513;
}


void	render_minimap(t_data *data)
{
	int		color;
	int		pixel_pos;
	char	c;

	int (i) = 0;
	int (j) = 0;
	int (x) = 0;
	int (y) = 0;
	while (i < 14)
	{
		j = 0;
		while (j < ft_strlen(data->map[i]))
		{
			if (data->map[i][j] == '1')
				color = 0xFFFFFF;
			else
				color = 0x0000FF;
			c = data->map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				color = 0x00FF00;
			x = 0;
			while (x < TILE_SIZE)
			{
				y = 0;
				while (y < TILE_SIZE)
				{
					pixel_pos = (i * TILE_SIZE + y) * (data->size_line / 4)
						+ (j * TILE_SIZE + x);
					data->img_data[pixel_pos] = color;
					y++;
				}
				x++;
			}
			j++;
		}
		i++;
	}
}
