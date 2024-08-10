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
void	render_frame(t_data *data)
{
	int (x) = 0;
	while (x < WIN_WIDTH)
	{
		cast_rays(data, x);
		x++;
	}
}

int	render_loop(t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	render_frame(data);
	render_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}

int main(int argc, char const **argv)
{
	t_data		data;

	if (check_args(argc, argv) != TRUE)
		error_msg("usage: ./cub3d <path/to/map.cub>", EXIT_FAILURE);

	init_mlx(&data);
	init_map(&data);
	init_player(&data);

	parse_map(&data, argv[1]);

	mlx_hook(data.win_ptr, 2, 1L<<0, handle_keypress, &data);
	mlx_loop_hook(data.mlx_ptr, render_loop, &data);
	mlx_loop(data.mlx_ptr);
}
