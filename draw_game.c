/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:40:38 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/25 16:41:29 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_ceiling_and_floor(t_data *data, int x)
{
	int (y) = -1;
	while (y++ < data->texture.draw_start)
		data->img_data[y * (data->size_line / 4) + x] = data->ceiling_color;
	y = data->texture.draw_end - 1;
	while (y++ < WIN_HEIGHT)
		data->img_data[y * (data->size_line / 4) + x] = data->floor_color;
}

static void	draw_wall_textures(t_data *data, int x, int dir)
{
	int		y;
	int		color;
	int		tex_y;

	y = data->texture.draw_start - 1;
	data->texture.step = 1.0 * TEXTURE_SIZE / data->rays->line_height;
	data->texture.pos = (data->texture.draw_start - WIN_HEIGHT / 2
			+ data->rays->line_height / 2) * data->texture.step;
	while (y++ < data->texture.draw_end)
	{
		tex_y = (int)data->texture.pos & (TEXTURE_SIZE - 1);
		data->texture.pos += data->texture.step;
		color = data->texture_buffer[dir][tex_y * TEXTURE_SIZE
			+ data->texture.tex_x];
		data->img_data[y * (data->size_line / 4) + x] = color;
	}
}

void	draw_game(t_data *data, int x)
{
	int		dir;

	calculate_for_textures(data);
	if (data->texture.draw_start < 0 || data->texture.draw_start >= WIN_HEIGHT
		|| data->texture.draw_end < 0 || data->texture.draw_end >= WIN_HEIGHT
		|| data->rays->line_height <= 0)
	{
		return ;
	}
	dir = set_dir(data);
	draw_ceiling_and_floor(data, x);
	draw_wall_textures(data, x, dir);
}
