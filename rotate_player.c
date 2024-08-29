/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:46:18 by marvin            #+#    #+#             */
/*   Updated: 2024/08/29 15:46:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_right(t_data *data)
{
	double (old_player_dir_x) = data->player.player_dir_x;
	data->player.player_dir_x = data->player.player_dir_x * cos(-ROT_SPEED)
		- data->player.player_dir_y * sin(-ROT_SPEED);
	data->player.player_dir_y = old_player_dir_x * sin(-ROT_SPEED)
		+ data->player.player_dir_y * cos(-ROT_SPEED);
	double (old_plane_x) = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(-ROT_SPEED)
		- data->player.plane_y * sin(-ROT_SPEED);
	data->player.plane_y = old_plane_x * sin(-ROT_SPEED) + data->player.plane_y
		* cos(-ROT_SPEED);
}

void	rotate_left(t_data *data)
{
	double (old_player_dir_x) = data->player.player_dir_x;
	data->player.player_dir_x = data->player.player_dir_x * cos(ROT_SPEED)
		- data->player.player_dir_y * sin(ROT_SPEED);
	data->player.player_dir_y = old_player_dir_x * sin(ROT_SPEED)
		+ data->player.player_dir_y * cos(ROT_SPEED);
	double (old_plane_x) = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(ROT_SPEED)
		- data->player.plane_y * sin(ROT_SPEED);
	data->player.plane_y = old_plane_x * sin(ROT_SPEED) + data->player.plane_y
		* cos(ROT_SPEED);
}
