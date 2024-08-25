/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:28:01 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/25 16:28:01 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_var_rays(t_data *data, int x)
{
	data->rays->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	data->rays->ray_dir_x = data->player.player_dir_x + data->player.plane_x
		* data->rays->camera_x;
	data->rays->ray_dir_y = data->player.player_dir_y + data->player.plane_y
		* data->rays->camera_x;
	data->rays->map_x = (int)data->player.player_x;
	data->rays->map_y = (int)data->player.player_y;
	data->rays->delta_dist_x = fabs(1 / data->rays->ray_dir_x);
	data->rays->delta_dist_y = fabs(1 / data->rays->ray_dir_y);
	data->rays->hit = 0;
	data->rays->step_x = 0;
	data->rays->step_y = 0;
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
		if (data->rays->map_x >= data->map_rows
			|| data->rays->map_y >= data->map_columns)
		{
			data->rays->hit = -1;
			break ;
		}
		if (data->map[data->rays->map_x][data->rays->map_y] == '1')
		{
			data->rays->hit = 1;
		}
	}
}

void	calculate_step_and_side(t_data *data)
{
	if (data->rays->ray_dir_x < 0)
	{
		data->rays->step_x = -1;
		data->rays->side_dist_x = (data->player.player_x - data->rays->map_x)
			* data->rays->delta_dist_x;
	}
	else
	{
		data->rays->step_x = 1;
		data->rays->side_dist_x = (data->rays->map_x + 1.0
				- data->player.player_x) * data->rays->delta_dist_x;
	}
	if (data->rays->ray_dir_y < 0)
	{
		data->rays->step_y = -1;
		data->rays->side_dist_y = (data->player.player_y - data->rays->map_y)
			* data->rays->delta_dist_y;
	}
	else
	{
		data->rays->step_y = 1;
		data->rays->side_dist_y = (data->rays->map_y + 1.0
				- data->player.player_y) * data->rays->delta_dist_y;
	}
}

void	cast_rays(t_data *data, int x)
{
	init_var_rays(data, x);
	calculate_step_and_side(data);
	check_hit(data);
	if (data->rays->side == 0)
		data->rays->perp_wall_dist = (data->rays->map_x - data->player.player_x
				+ (1 - data->rays->step_x) / 2) / data->rays->ray_dir_x;
	else
		data->rays->perp_wall_dist = (data->rays->map_y - data->player.player_y
				+ (1 - data->rays->step_y) / 2) / data->rays->ray_dir_y;
	data->rays->line_height = (int)(WIN_HEIGHT / data->rays->perp_wall_dist);
}
