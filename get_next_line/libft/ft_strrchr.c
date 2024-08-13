/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:51:05 by rrisseli          #+#    #+#             */
/*   Updated: 2024/01/24 12:06:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	to_find;

	to_find = (unsigned char)c;
	i = ft_strlen((char *)s);
	while ((s[i] == to_find) || (i > 0))
	{
		if (s[i] == to_find)
		{
			return ((char *)&s[i]);
		}
		i--;
	}
	return (NULL);
}
