/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:25:59 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/25 16:25:59 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_data *data)
{
	if (data->map[(int)(data->player.player_x + data->player.player_dir_x
			* MOVE_SPEED)][(int)data->player.player_y] == '0')
		data->player.player_x += data->player.player_dir_x * MOVE_SPEED;
	if (data->map[(int)data->player.player_x][(int)(data->player.player_y
		+ data->player.player_dir_y * MOVE_SPEED)] == '0')
		data->player.player_y += data->player.player_dir_y * MOVE_SPEED;
}

void	move_backward(t_data *data)
{
	if (data->map[(int)(data->player.player_x - data->player.player_dir_x
			* MOVE_SPEED)][(int)data->player.player_y] == '0')
		data->player.player_x -= data->player.player_dir_x * MOVE_SPEED;
	if (data->map[(int)data->player.player_x][(int)(data->player.player_y
		- data->player.player_dir_y * MOVE_SPEED)] == '0')
		data->player.player_y -= data->player.player_dir_y * MOVE_SPEED;
}

void	move_left(t_data *data)
{
	if (data->map[(int)(data->player.player_x - data->player.plane_x
			* MOVE_SPEED)][(int)data->player.player_y] == '0')
		data->player.player_x -= data->player.plane_x * MOVE_SPEED;
	if (data->map[(int)data->player.player_x][(int)(data->player.player_y
		- data->player.plane_y * MOVE_SPEED)] == '0')
		data->player.player_y -= data->player.plane_y * MOVE_SPEED;
}

void	move_right(t_data *data)
{
	if (data->map[(int)(data->player.player_x + data->player.plane_x
			* MOVE_SPEED)][(int)data->player.player_y] == '0')
		data->player.player_x += data->player.plane_x * MOVE_SPEED;
	if (data->map[(int)data->player.player_x][(int)(data->player.player_y
		+ data->player.plane_y * MOVE_SPEED)] == '0')
		data->player.player_y += data->player.plane_y * MOVE_SPEED;
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == 122)
		move_forward(data);
	if (keycode == 115)
		move_backward(data);
	if (keycode == 100)
		move_right(data);
	if (keycode == 113)
		move_left(data);
	if (keycode == 65363)
		rotate_right(data);
	if (keycode == 65361)
		rotate_left(data);
	if (keycode == 65307)
		close_window(data);
	return (0);
}
