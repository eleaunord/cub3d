/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:12:09 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/25 19:17:06 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_data *game)
{
	size_t	i;

	if (game->map)
	{
		i = 0;
		while (i < game->map_rows)
		{
			if (game->map[i])
				free(game->map[i]);
			i++;
		}
		free(game->map);
		game->map = NULL;
	}
}

void clean_mlx(t_data *game)
{
    if (!game)
        return;
    if (game->img_ptr)
        mlx_destroy_image(game->mlx_ptr, game->img_ptr);
    if (game->win_ptr)
        mlx_destroy_window(game->mlx_ptr, game->win_ptr);
}

void	clean_up(t_data *game)
{
	if (!game)
		return ;
	if (game->no)
	{
		free(game->no);
		game->no = NULL;
	}
	if (game->so)
	{
		free(game->so);
		game->so = NULL;
	}
	if (game->we)
	{
		free(game->we);
		game->we = NULL;
	}
	if (game->ea)
	{
		free(game->ea);
		game->ea = NULL;
	}
	if (game->map)
		free_map(game);
	// free texture buffer
}

int	error_msg(t_data *game, char *mess, int status)
{
	if (game->line)
		free(game->line);
	if (game->fd > 0)
	{
		get_next_line(game->fd, 1);
		close(game->fd);
	}
	clean_up(game);
	clean_mlx(game);
	ft_putstr_fd("cub3D: Error", 2);
	if (mess)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(mess, 2);
	}
	exit(status);
}
