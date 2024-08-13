/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 00:04:35 by marvin            #+#    #+#             */
/*   Updated: 2024/07/27 00:04:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
		1111111111111111111111111
		1000000000110000000000001
		1011000001110000000000001
		1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
*/
// void	render_frame(t_data *data)
// {
// 	int (x) = 0;
// 	while (x < WIN_WIDTH)
// 	{
// 		cast_rays(data, x);
// 		x++;
// 	}
// }

// int	render_loop(t_data *data)
// {
// 	mlx_clear_window(data->mlx_ptr, data->win_ptr);
// 	render_frame(data);
// 	render_minimap(data);
// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
// 	return (0);
// }

void	init_game(t_data *game)
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
void set_hero_orientation(t_data *game, char c)
{
	if (c == 'N')
		game->hero_orientation = 'N';
	else if (c == 'S')
		game->hero_orientation = 'S';
	else if (c == 'E')
		game->hero_orientation = 'E';
	else if (c == 'W')
		game->hero_orientation = 'W';
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
				game->row_start_position = i;
				game->col_start_position = j;
				return;
			}
		}
	}
	error_msg(game, "Hero not found in map.\n", EXIT_FAILURE);
}

int main(int argc, char const **argv)
{
	t_data		data;

	if (check_args(argc, argv) != true)
	{
		write(2, "valid format is : ./cub3d <path/to/map.cub>\n", 44);
		exit(EXIT_FAILURE);
	}

	ft_bzero(&data, sizeof(t_data));
	init_game(&data);
	// init_mlx(&data);
	// init_map(&data);
	// init_player(&data);

	parse_file(&data, argv[1]);
	init_hero_pos(&data);
	// printf("Hero Orientation: %c\n", data.hero_orientation);
	// printf("Start Position: row[%ld]col[%ld]\n", data.row_start_position, data.col_start_position);

	// mlx_hook(data.win_ptr, 2, 1L<<0, handle_keypress, &data);
	// mlx_loop_hook(data.mlx_ptr, render_loop, &data);
	// mlx_loop(data.mlx_ptr);
}
