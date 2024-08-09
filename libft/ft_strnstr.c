/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:18:32 by marvin            #+#    #+#             */
/*   Updated: 2023/11/09 14:18:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	s1k;
	size_t	s2k;
	size_t	s2_len;

	if ((!s1 || !s2) && !len)
		return (0);
	s2_len = ft_strlen(s2);
	if (!s2_len)
		return ((char *)s1);
	s1k = 0;
	while (s1[s1k] && (len - (size_t)s1k >= s2_len))
	{
		s2k = 0;
		while (s2[s2k])
		{
			if (s1[s1k + s2k] != s2[s2k])
				break ;
			s2k++;
		}
		if (s2k == s2_len)
			return ((char *)s1 + s1k);
		s1k++;
	}
	return (0);
}
