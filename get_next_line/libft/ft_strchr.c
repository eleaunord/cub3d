/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:12:49 by rrisseli          #+#    #+#             */
/*   Updated: 2024/01/24 12:05:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	to_find;

	to_find = (unsigned char)c;
	i = 0;
	while ((s[i] == to_find) || (s[i] != '\0'))
	{
		if (s[i] == to_find)
		{
			return ((char *)s + i);
		}
		i++;
	}
	return (NULL);
}
