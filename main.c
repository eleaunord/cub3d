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

void    draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
	{
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy){ err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
	}
}

void cast_rays(t_data *data, int x)
{
    double (camera_x) = 2 * x / (double)WIN_WIDTH - 1;
    double (ray_dir_x) = data->player_dir_x + data->plane_x * camera_x;
    double (ray_dir_y) = data->player_dir_y + data->plane_y * camera_x;
    int (map_x) = (int)data->player_x;
    int (map_y) = (int)data->player_y;
    double (side_dist_x);
    double (side_dist_y);
    double (delta_dist_x) = fabs(1 / ray_dir_x);
    double (delta_dist_y) = fabs(1 / ray_dir_y);
    double (perp_wall_dist);
    int (step_x);
    int (step_y);
    int (hit) = 0;
    int (side);
    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (data->player_x - map_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - data->player_x) * delta_dist_x;
    }
    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (data->player_y - map_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - data->player_y) * delta_dist_y;
    }
    while (hit == 0)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;
        }
        if (data->map[map_x][map_y] == '1')
            hit = 1;
    }

    if (side == 0)
        perp_wall_dist = (map_x - data->player_x + (1 - step_x) / 2) / ray_dir_x;
    else
        perp_wall_dist = (map_y - data->player_y + (1 - step_y) / 2) / ray_dir_y;

    int (line_height) = (int)(WIN_HEIGHT / perp_wall_dist);

    int (draw_start) = -line_height / 2 + WIN_HEIGHT / 2;
    if (draw_start < 0)
        draw_start = 0;
    int (draw_end) = line_height / 2 + WIN_HEIGHT / 2;
    if (draw_end >= WIN_HEIGHT)
        draw_end = WIN_HEIGHT - 1;

    int (color);
    if (side == 0)
        color = 0xFF0000;
    else
        color = 0x00FF00;

    int (y) = draw_start;
    while (y < draw_end)
    {
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
        y++;
    }
}

void    render_frame(t_data *data)
{
    int (x) = 0;
    while (x < WIN_WIDTH)
    {
        cast_rays(data, x);
        x++;
    }
}

int	main(void)
{
	t_data		data;

	init_mlx(&data);
	init_map(&data);
    init_player(&data);
	render_minimap(&data);
	render_frame(&data);
	mlx_loop(data.mlx_ptr);

}