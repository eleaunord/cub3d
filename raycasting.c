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

void	init_var_rays(t_data *data, int x)
{
	data->rays->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	data->rays->ray_dir_x = data->player_dir_x + data->plane_x
		* data->rays->camera_x;
	data->rays->ray_dir_y = data->player_dir_y + data->plane_y
		* data->rays->camera_x;
	data->rays->map_x = (int)data->player_x;
	data->rays->map_y = (int)data->player_y;
	data->rays->delta_dist_x = fabs(1 / data->rays->ray_dir_x);
	data->rays->delta_dist_y = fabs(1 / data->rays->ray_dir_y);
	data->rays->hit = 0;
}

void	draw_game(t_data *data, int x)
{
	int	color;

	int (draw_start) = -(data->rays->line_height) / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	int (draw_end) = data->rays->line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	if (data->rays->side == 0)
		color = 0xFF0000;
	else
		color = 0x00FF00;
	int (y) = draw_start;
	while (y < draw_end)
	{
		data->img_data[y * WIN_WIDTH + x] = color;
		y++;
	}
}

void	check_hit(t_data *data)
{
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
		if (data->map[data->rays->map_x][data->rays->map_y] == '1')
			data->rays->hit = 1;
	}
}

void	cast_rays(t_data *data, int x)
{
	init_var_rays(data, x);
	if (data->rays->ray_dir_x < 0)
	{
		data->rays->step_x = -1;
		data->rays->side_dist_x = (data->player_x - data->rays->map_x)
			* data->rays->delta_dist_x;
	}
	else
	{
		data->rays->step_x = 1;
		data->rays->side_dist_x = (data->rays->map_x + 1.0 - data->player_x)
			* data->rays->delta_dist_x;
	}
	if (data->rays->ray_dir_y < 0)
	{
		data->rays->step_y = -1;
		data->rays->side_dist_y = (data->player_y - data->rays->map_y)
			* data->rays->delta_dist_y;
	}
	else
	{
		data->rays->step_y = 1;
		data->rays->side_dist_y = (data->rays->map_y + 1.0 - data->player_y)
			* data->rays->delta_dist_y;
	}
	check_hit(data);
	if (data->rays->side == 0)
		data->rays->perp_wall_dist = (data->rays->map_x - data->player_x
				+ (1 - data->rays->step_x) / 2) / data->rays->ray_dir_x;
	else
		data->rays->perp_wall_dist = (data->rays->map_y - data->player_y
				+ (1 - data->rays->step_y) / 2) / data->rays->ray_dir_y;
	data->rays->line_height = (int)(WIN_HEIGHT / data->rays->perp_wall_dist);
	draw_game(data, x);
}
