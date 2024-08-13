/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_gnl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:34:42 by marvin            #+#    #+#             */
/*   Updated: 2024/01/18 14:34:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *backup, char *buffer)
{
	size_t		i;
	size_t		j;
	char		*str;

	if (!backup)
	{
		backup = malloc(1 * sizeof(char));
		backup[0] = '\0';
	}
	if (!backup || !buffer)
		return (0);
	str = malloc(sizeof(char) * ((ft_strlen(backup) + ft_strlen(buffer)) + 1));
	if (!str)
		return (0);
	i = -1;
	j = 0;
	if (backup)
		while (backup[++i] != '\0')
			str[i] = backup[i];
	while (buffer[j] != '\0')
		str[i++] = buffer[j++];
	str[i] = '\0';
	free(backup);
	return (str);
}
