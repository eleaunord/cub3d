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

void	init_map(t_data *data)
{
	data->map = malloc(sizeof(char *) * 14);
	data->map[0] = ft_strdup("        1111111111111111111111111");
	data->map[1] = ft_strdup("        1000000000110000000000001");
	data->map[2] = ft_strdup("        1011000001110000000000001");
	data->map[3] = ft_strdup("        1001000000000000001000001");
	data->map[4] = ft_strdup("111111111011000001110000000000001");
	data->map[5] = ft_strdup("100000000011000001110111100111111");
	data->map[6] = ft_strdup("11110111111111011100000010001");
	data->map[7] = ft_strdup("11110111111111011101010010001");
	data->map[8] = ft_strdup("11000000110101011100000010001");
	data->map[9] = ft_strdup("10000000000000001100000010001");
	data->map[10] = ft_strdup("10000000000000001101010010001");
	data->map[11] = ft_strdup("11000001110101011111011110N0111");
	data->map[12] = ft_strdup("11110111 1110101 101111010001");
	data->map[13] = ft_strdup("11111111 1111111 111111111111");
	data->player_x = 11;
	data->player_y = 26;
	data->player_dir_x = -1;
	data->player_dir_y = 0;
    data->plane_x = 0;
    data->plane_y = 0.66;
}

void	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
}

void render_minimap(t_data *data)
{
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
    while (i < 14)
	{
		j = 0;
        while (j < ft_strlen(data->map[i]))
		{
            int color = data->map[i][j] == '1' ? 0xFFFFFF : 0x0000FF;
			char (c) = data->map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				color = 0x00FF00;
			
			x = 0;
            while (x < TILE_SIZE)
			{
				y = 0;
                while (y < TILE_SIZE)
				{
                    mlx_pixel_put(data->mlx_ptr, data->win_ptr, j * TILE_SIZE + x, i * TILE_SIZE + y, color);
					y++;
                }
				x++;
            }
			j++;
        }
		i++;
    }
}