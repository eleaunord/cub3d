/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:12:29 by marvin            #+#    #+#             */
/*   Updated: 2024/08/08 19:12:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_var_rays(t_data *data, int x)
{
	data->rays->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	data->rays->ray_dir_x = data->player.player_dir_x + data->player.plane_x * data->rays->camera_x;
	data->rays->ray_dir_y = data->player.player_dir_y + data->player.plane_y * data->rays->camera_x;
	data->rays->map_x = (int)data->player.player_x;
	data->rays->map_y = (int)data->player.player_y;
	data->rays->delta_dist_x = fabs(1 / data->rays->ray_dir_x);
	data->rays->delta_dist_y = fabs(1 / data->rays->ray_dir_y);
	data->rays->hit = 0;
}
void draw_game(t_data *data, int x)
{
	int color;
	int y;

	int draw_start = -(data->rays->line_height) / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	int draw_end = data->rays->line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;

	if (data->rays->side == 0)
		color = (data->rays->ray_dir_x > 0) ? 0xFF0000 : 0x00FF00;
	else
		color = (data->rays->ray_dir_y > 0) ? 0x0000FF : 0xFFFF00;
	y = 0;
	while (y < draw_start)
	{
		if ((x >= 0 && x < WIN_WIDTH )&& (y >= 0 && y < WIN_HEIGHT))
		{
			data->img_data[y * (data->size_line / 4) + x] = data->ceiling_color;
		}
		y++;
	}
	while (y < draw_end)
	{
		if ((x >= 0 && x < WIN_WIDTH) &&( y >= 0 && y < WIN_HEIGHT))
			data->img_data[y * (data->size_line / 4) + x] = color;
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		if ((x >= 0 && x < WIN_WIDTH )&& (y >= 0 && y < WIN_HEIGHT))
			data->img_data[y * (data->size_line / 4) + x] = data->floor_color;
		y++;
	}
}

void check_hit(t_data *data)
{
	int map_width = WIN_WIDTH;
	int map_height = WIN_HEIGHT;

	while (data->rays->hit == 0)
	{
		if (data->rays->side_dist_x < data->rays->side_dist_y)
		{
			data->rays->side_dist_x += data->rays->delta_dist_x;
			data->rays->map_x += data->rays->step_x;
			data->rays->side = 0;
		}
		else
		{
			data->rays->side_dist_y += data->rays->delta_dist_y;
			data->rays->map_y += data->rays->step_y;
			data->rays->side = 1;
		}
		if (data->rays->map_x >= 0 && data->rays->map_x < map_width &&
			data->rays->map_y >= 0 && data->rays->map_y < map_height)
		{
			if (data->map[data->rays->map_x][data->rays->map_y] == '1')
				data->rays->hit = 1;
		}
		else
		{
			data->rays->hit = 1;
		}
	}
}

void calculate_step_and_side(t_data *data)
{
	if (data->rays->ray_dir_x < 0)
	{
		data->rays->step_x = -1;
		data->rays->side_dist_x = (data->player.player_x - data->rays->map_x) * data->rays->delta_dist_x;
	}
	else
	{
		data->rays->step_x = 1;
		data->rays->side_dist_x = (data->rays->map_x + 1.0 - data->player.player_x) * data->rays->delta_dist_x;
	}
	if (data->rays->ray_dir_y < 0)
	{
		data->rays->step_y = -1;
		data->rays->side_dist_y = (data->player.player_y - data->rays->map_y) * data->rays->delta_dist_y;
	}
	else
	{
		data->rays->step_y = 1;
		data->rays->side_dist_y = (data->rays->map_y + 1.0 - data->player.player_y) * data->rays->delta_dist_y;
	}
}

void cast_rays(t_data *data, int x)
{
	init_var_rays(data, x);
	calculate_step_and_side(data);
	check_hit(data);
	if (data->rays->side == 0)
		data->rays->perp_wall_dist = (data->rays->map_x - data->player.player_x + (1 - data->rays->step_x) / 2) / data->rays->ray_dir_x;
	else
		data->rays->perp_wall_dist = (data->rays->map_y - data->player.player_y + (1 - data->rays->step_y) / 2) / data->rays->ray_dir_y;
	data->rays->line_height = (int)(WIN_HEIGHT / data->rays->perp_wall_dist);
	draw_game(data, x);
}