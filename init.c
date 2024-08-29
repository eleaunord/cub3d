/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:23:02 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/25 16:23:02 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game_input(t_data *game)
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
	game->fd = -1;
	game->hero = 0;
}

static void	set_player_plane(t_player *player, char c)
{
	if (c == 'N')
	{
		player->plane_y = 0.66;
		player->plane_x = 0;
	}
	else if (c == 'S')
	{
		player->plane_y = -0.66;
		player->plane_x = 0;
	}
	else if (c == 'E')
	{
		player->plane_y = 0;
		player->plane_x = 0.66;
	}
	else if (c == 'W')
	{
		player->plane_y = 0;
		player->plane_x = -0.66;
	}
}

static void	set_player_direction(t_player *player, char c)
{
	if (c == 'N')
	{
		player->player_dir_y = 0;
		player->player_dir_x = -1;
	}
	else if (c == 'S')
	{
		player->player_dir_y = 0;
		player->player_dir_x = 1;
	}
	else if (c == 'E')
	{
		player->player_dir_y = 1;
		player->player_dir_x = 0;
	}
	else if (c == 'W')
	{
		player->player_dir_y = -1;
		player->player_dir_x = 0;
	}
}

void	init_hero_pos(t_data *game)
{
	size_t (i) = -1;
	size_t (j) = -1;
	while (++i < game->map_rows)
	{
		j = -1;
		while (++j < game->map_columns)
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				set_player_direction(&game->player, game->map[i][j]);
				set_player_plane(&game->player, game->map[i][j]);
				game->player.player_x = i;
				game->player.player_y = j;
				if (game->map[i + 1] && game->map[i + 1][j] != '1')
					game->player.player_x += 0.1;
				else
					game->player.player_y += 0.1;
				if ((game->map[i][j] == 'E' || game->map[i][j] == 'W')
					&& game->map[i][j - 1] == '1')
					game->player.player_y += 0.2;
				game->map[i][j] = '0';
				return ;
			}
		}
	}
	error_msg(game, "Hero not found in map.\n", EXIT_FAILURE);
}

void	init_graphics(t_data *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		error_msg(game, "Error initializing mlx\n", EXIT_FAILURE);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"Cub3D");
	if (!game->win_ptr)
		error_msg(game, "Error creating window\n", EXIT_FAILURE);
	game->img_ptr = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img_ptr)
		error_msg(game, "Error on mlx new image\n", EXIT_FAILURE);
	game->img_data = (int *)mlx_get_data_addr(game->img_ptr, &game->bpp,
			&game->size_line, &game->endian);
	if (!game->img_data)
		error_msg(game, "Error on mlx get data addr\n", EXIT_FAILURE);
	game->rays = ft_calloc(1, sizeof(t_raycasting));
	if (!game->rays)
		error_msg(game, "Failed malloc on rays\n", EXIT_FAILURE);
}
