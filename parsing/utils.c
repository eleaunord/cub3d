/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:56:29 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/25 16:05:20 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_number(char *str)
{
	size_t	i;
	int		result;

	i = 0;
	result = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ')
			return (0);
		if (ft_isdigit(str[i]))
			result = result * 10 + str[i] - '0';
		if (result > 255)
			return (0);
		i++;
	}
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (ft_strlen(str) == i)
		return (0);
	return (1);
}

int	ft_array_len(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
