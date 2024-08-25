/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:55:00 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/25 15:55:20 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*trim_and_check_line(char *line, t_data *game)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, "\r\n");
	if (!trimmed_line)
	{
		free(line);
		error_msg(game, "Memory allocation failed for trimmed line.\n",
			EXIT_FAILURE);
	}
	return (trimmed_line);
}

static int	find_row_index(t_data *game)
{
	size_t	row_index;

	row_index = 0;
	while (row_index < game->map_rows && game->map[row_index] != NULL)
		row_index++;
	if (row_index >= game->map_rows)
		error_msg(game, "Too many map rows.\n", EXIT_FAILURE);
	return (row_index);
}

static void	allocate_map_row(t_data *game, int row_index, char *trimmed_line)
{
	game->map[row_index] = ft_calloc(game->map_columns + 1, sizeof(char));
	if (!game->map[row_index])
	{
		free(trimmed_line);
		error_msg(game, "Memory allocation failed for map row.\n",
			EXIT_FAILURE);
	}
	game->map[row_index][game->map_columns] = '\0';
}

static void	copy_line_to_map(t_data *game, int row_index, char *trimmed_line)
{
	size_t	j;
	size_t	trimmed_length;

	trimmed_length = ft_strlen(trimmed_line);
	j = -1;
	while (++j < trimmed_length)
	{
		if (trimmed_line[j] == ' ')
			game->map[row_index][j] = '1';
		else if (is_valid_char(game, trimmed_line[j]))
			game->map[row_index][j] = trimmed_line[j];
		else
		{
			free(trimmed_line);
			get_next_line(game->fd, 1);
			error_msg(game, "Invalid character in map line.\n", EXIT_FAILURE);
		}
	}
	while (j < game->map_columns)
	{
		game->map[row_index][j] = '1';
		j++;
	}
	game->map[row_index][j] = '\0';
}

void	fill_map(t_data *game, char *line)
{
	char	*trimmed_line;
	int		row_index;

	trimmed_line = trim_and_check_line(line, game);
	free(line);
	if (game->map_rows <= 0)
	{
		free(trimmed_line);
		error_msg(game, "Map not set properly.\n", EXIT_FAILURE);
	}
	row_index = find_row_index(game);
	allocate_map_row(game, row_index, trimmed_line);
	copy_line_to_map(game, row_index, trimmed_line);
	free(trimmed_line);
}
