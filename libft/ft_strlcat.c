/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:30:33 by rrisseli          #+#    #+#             */
/*   Updated: 2024/01/24 12:11:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *s1, const char *s2, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < size && s1[i])
	{
		i++;
	}
	while ((i + j + 1) < size && s2[j])
	{
		s1[i + j] = s2[j];
		j++;
	}
	if (i != size)
	{
		s1[i + j] = '\0';
	}
	return (i + ft_strlen((char *)s2));
}
