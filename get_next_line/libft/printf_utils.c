/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrisseli <rrisseli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:32:00 by rrisseli          #+#    #+#             */
/*   Updated: 2023/12/18 16:32:00 by rrisseli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

int	ft_printd(int nb)
{
	int		size;
	long	n;

	n = nb;
	size = 0;
	if (n < 0)
	{
		size += ft_putchar('-');
		n = -n;
	}
	if (n / 10)
		size += ft_printd(n / 10);
	return (ft_putchar(n % 10 + '0') + size);
}

int	ft_printuns(unsigned int nb)
{
	int	size;

	size = 0;
	if (nb / 10)
		size += ft_printuns(nb / 10);
	return (ft_putchar(nb % 10 + '0') + size);
}
