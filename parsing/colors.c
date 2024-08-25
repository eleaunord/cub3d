/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:53:46 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/25 16:03:20 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_commas(t_data *game, char *line, int *i)
{
	int	count;
	int	start_index;

	start_index = *i;
	count = 0;
	while (line[*i] != '\0')
	{
		if (line[*i] == ',')
			count++;
		(*i)++;
	}
	if (count != 2)
		error_msg(game, "Invalid color format.\n", EXIT_FAILURE);
	*i = start_index;
}

static void	skip_whitespace(const char *line, int *i)
{
	while (line[*i] != '\0' && is_space(line[*i]))
		(*i)++;
}

static void	parse_rgb_component(const char *line, int *i, int *component)
{
	if (!ft_isdigit(line[*i]))
		error_msg(NULL, "Invalid color value digit.\n", EXIT_FAILURE);
	*component = 0;
	while (line[*i] != '\0' && ft_isdigit(line[*i]))
	{
		*component = *component * 10 + (line[*i] - '0');
		(*i)++;
	}
}

static void	check_color_format(t_data *game, char *line, int *i, int *rgb)
{
	int	j;

	check_commas(game, line, i);
	j = 0;
	while (line[*i] != '\0')
	{
		skip_whitespace(line, i);
		if (line[*i] == ',')
		{
			(*i)++;
			continue ;
		}
		if (!ft_isdigit(line[*i]))
			error_msg(game, "Invalid color value digit.\n", EXIT_FAILURE);
		parse_rgb_component(line, i, &rgb[j]);
		if (rgb[j] > 255 || rgb[j] < 0)
			error_msg(game, "Invalid color value.\n", EXIT_FAILURE);
		j++;
		if (j == 3 && line[*i] != '\0')
			error_msg(game, "Invalid color format.\n", EXIT_FAILURE);
	}
	if (j != 3)
		error_msg(game, "Invalid color format.\n", EXIT_FAILURE);
}

void	get_color_code(t_identifier color, char *line, t_data *game)
{
	int	i;
	int	rgb[3];
	int	color_hex;

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	if (is_already_loaded(game, color) == true)
		error_msg(game, "Color is already loaded.\n", EXIT_FAILURE);
	i = 1;
	while (line[i] != '\0' && is_space(line[i]))
		i++;
	check_color_format(game, line, &i, rgb);
	color_hex = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	if (color == F)
		game->floor_color = color_hex;
	else if (color == C)
		game->ceiling_color = color_hex;
}
