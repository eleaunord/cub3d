/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:51:46 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 12:51:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_sep(char c, char charset)
{
	if (c == charset)
		return (1);
	if (c == '\0')
		return (1);
	return (0);
}

static int	count_words(char *str, char c)
{
	int	i;
	int	cw;

	cw = 0;
	i = 0;
	while (str[i])
	{
		if (check_sep(str[i + 1], c) == 1 && check_sep(str[i],
				c) == 0)
			cw++;
		i++;
	}
	return (cw);
}

static void	word_copy(char *dest, char *src, char c)
{
	int	i;

	i = 0;
	while (check_sep(src[i], c) == 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static void	split_words(char **array, char *str, char c)
{
	int	i;
	int	j;
	int	word;

	word = 0;
	i = 0;
	while (str[i])
	{
		if (check_sep(str[i], c) == 1)
			i++;
		else
		{
			j = 0;
			while (check_sep(str[i + j], c) == 0)
				j++;
			array[word] = (char *)malloc(sizeof(char) * (j + 1));
			word_copy(array[word], str + i, c);
			i += j;
			word++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		words;

	words = count_words((char *)s, c);
	array = malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array[words] = 0;
	split_words(array, (char *)s, c);
	return (array);
}
