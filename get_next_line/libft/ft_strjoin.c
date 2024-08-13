/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:25:07 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 12:25:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*string;
	size_t	length;

	length = ft_strlen(s1);
	if (!s1 || !s2)
		return (NULL);
	string = ft_calloc(length + ft_strlen(s2) + 1, sizeof(char));
	if (!string)
		return (NULL);
	ft_strlcpy(string, s1, length + 1);
	while (*s2)
		string[length++] = *s2++;
	return (string);
}
