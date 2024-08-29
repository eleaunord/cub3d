/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:23:56 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/25 16:23:56 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_frame(t_data *data)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		cast_rays(data, x);
		draw_game(data, x);
		x++;
	}
}

int	render_loop(t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	render_frame(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}

int	close_window(t_data *game)
{
	if (game)
	{
		clean_up(game);
		free(game->rays);
		free(game->texture_buffer[0]);
		free(game->texture_buffer[1]);
		free(game->texture_buffer[2]);
		free(game->texture_buffer[3]);
		clean_mlx(game);
	}
	exit (0);
}

int	main(int argc, char const **argv)
{
	t_data	data;

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
