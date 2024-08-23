/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:18:04 by marvin            #+#    #+#             */
/*   Updated: 2024/08/13 21:18:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	Calculate the exact position on the wall hit by the ray
	Calculate the x coordinate on the texture
	Calculate the range of pixels to draw on the screen*/
void calculate_for_textures(t_data *data)
{
	if (data->rays->side == 0)
	{
		data->texture.wall_x = data->player.player_y + data->rays->perp_wall_dist * data->rays->ray_dir_y;
	}
	else
	{
		data->texture.wall_x = data->player.player_x + data->rays->perp_wall_dist * data->rays->ray_dir_x;
	}
	data->texture.wall_x -= floor(data->texture.wall_x);
	data->texture.tex_x = (int)(data->texture.wall_x * (double)TEXTURE_SIZE);
	if ((data->rays->side == 0 && data->rays->ray_dir_x < 0) || (data->rays->side == 1 && data->rays->ray_dir_y > 0))
	{
		data->texture.tex_x = TEXTURE_SIZE - data->texture.tex_x - 1;
	}
	data->texture.draw_start = -(data->rays->line_height) / 2 + WIN_HEIGHT / 2;
	data->texture.draw_end = data->rays->line_height / 2 + WIN_HEIGHT / 2;
	if (data->texture.draw_start < 0)
		data->texture.draw_start = 0;
	if (data->texture.draw_end >= WIN_HEIGHT)
		data->texture.draw_end = WIN_HEIGHT - 1;
	if (data->texture.draw_end < 0)
		data->texture.draw_end = 0;
}

int set_dir(t_data *data)
{
	int dir;

	if (data->rays->side == 0)
	{
		if (data->rays->ray_dir_x > 0)
			dir = NORTH;
		else
			dir = SOUTH;
	}
	else
	{
		if (data->rays->ray_dir_y > 0)
			dir = EAST;
		else
			dir = WEST;
	}
	return (dir);
}
void draw_game(t_data *data, int x)
{
	int color;
	int dir;
	int tex_y;

	int(y) = -1;
	calculate_for_textures(data);
	if (data->texture.draw_start < 0 || data->texture.draw_start >= WIN_HEIGHT ||
		data->texture.draw_end < 0 || data->texture.draw_end >= WIN_HEIGHT ||
		data->rays->line_height <= 0)
	{
		return;
	}
	while (y++ < data->texture.draw_start)
		data->img_data[y * (data->size_line / 4) + x] = data->ceiling_color;
	data->texture.step = 1.0 * TEXTURE_SIZE / data->rays->line_height;
	data->texture.pos = (data->texture.draw_start - WIN_HEIGHT / 2 + data->rays->line_height / 2) * data->texture.step;
	y = data->texture.draw_start - 1;
	dir = set_dir(data);
	while (y++ < data->texture.draw_end)
	{
		tex_y = (int)data->texture.pos & (TEXTURE_SIZE - 1);
		data->texture.pos += data->texture.step;
		color = data->texture_buffer[dir][tex_y * TEXTURE_SIZE + data->texture.tex_x];
		data->img_data[y * (data->size_line / 4) + x] = color;
	}
	y = data->texture.draw_end - 1;
	while (y++ < WIN_HEIGHT)
		data->img_data[y * (data->size_line / 4) + x] = data->floor_color;
}


void	load_texture_to_buffer(t_data *data, int index, char *file_path)
{
	int		width;
	int		height;
	void	*img_texture_ptr;
	int		x;

	img_texture_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			file_path, &width, &height);
	data->texture.image_texture_data = (int *)mlx_get_data_addr(img_texture_ptr,
			&data->texture.bpp, &data->texture.size_line,
			&data->texture.endian);
	data->texture_buffer[index] = malloc(sizeof(int)
			* TEXTURE_SIZE * TEXTURE_SIZE);
	int (y) = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			data->texture_buffer[index][y * width + x]
				= data->texture.image_texture_data[y * width + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(data->mlx_ptr, img_texture_ptr);
}

void	init_textures(t_data *data)
{
	load_texture_to_buffer(data, NORTH, data->no);
	load_texture_to_buffer(data, SOUTH, data->so);
	load_texture_to_buffer(data, EAST, data->ea);
	load_texture_to_buffer(data, WEST, data->we);
}
