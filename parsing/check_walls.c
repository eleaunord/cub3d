/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:09:20 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/25 16:11:16 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_horizontal_borders(t_data *game, size_t row_length)
{
	size_t	i;

	i = 0;
	while (i < row_length)
	{
		if (game->map[0][i] != '1')
			error_msg(game,
				"Top border of the map must be enclosed by walls.\n",
				EXIT_FAILURE);
		if (game->map[game->map_rows - 1][i] != '1')
			error_msg(game,
				"Bottom border of the map must be enclosed by walls.\n",
				EXIT_FAILURE);
		i++;
	}
}

static void	check_vertical_borders(t_data *game, size_t row_length)
{
	size_t	i;

	i = 1;
	while (i < game->map_rows - 1)
	{
		if (game->map[i][0] != '1')
			error_msg(game,
				"Left border of the map must be enclosed by walls.\n",
				EXIT_FAILURE);
		if (game->map[i][row_length - 1] != '1')
			error_msg(game,
				"Right border of the map must be enclosed by walls.\n",
				EXIT_FAILURE);
		i++;
	}
}

void	check_map_walls(t_data *game)
{
	size_t	row_length;

	if (game->map_rows < 2)
		error_msg(game, "Map must have at least two rows.\n", EXIT_FAILURE);
	row_length = ft_strlen(game->map[0]);
	check_horizontal_borders(game, row_length);
	check_vertical_borders(game, row_length);
}
