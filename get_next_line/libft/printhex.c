/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printhex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:46:23 by rrisseli          #+#    #+#             */
/*   Updated: 2024/01/24 11:58:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(unsigned int nbr, char *base)
{
	int			len_base;
	long int	n;
	int			size;

	n = nbr;
	len_base = ft_strlen(base);
	size = 0;
	if (n >= len_base)
	{
		size += ft_putnbr_base(n / len_base, base);
		size += ft_putchar(base[n % len_base]);
	}
	else
	{
		size += ft_putchar(base[n]);
	}
	return (size);
}
