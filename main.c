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

//valgrind --leak-check=full --show-leak-kinds=all ./executable description.cub 2> leak.log

void render_frame(t_data *data)
{
	int x = 0;
	while (x < WIN_WIDTH)
	{
		cast_rays(data, x);
		draw_game(data, x);
		x++;
	}
}

int render_loop(t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	render_frame(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}

int close_window(t_data *game)
{
	if (game)
	{
		if (game->fd > 0)
		{
			get_next_line(game->fd, 1);
			close(game->fd);
			game->fd = -1;
		}
		clean_up(game);
		clean_mlx(game);
		free(game);
	}

	exit(EXIT_SUCCESS);
	return (0);
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
	init_game_input(&data);
	parse_file(&data, argv[1]);
	init_hero_pos(&data);
	init_graphics(&data);
	init_textures(&data);
	mlx_hook(data.win_ptr, 2, 1L << 0, handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, (1L << 1), close_window, &data);
	mlx_loop_hook(data.mlx_ptr, render_loop, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
