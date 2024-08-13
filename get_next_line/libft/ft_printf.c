/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrisseli <rrisseli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:31:40 by rrisseli          #+#    #+#             */
/*   Updated: 2023/12/18 16:31:40 by rrisseli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_triprintf(const char format, va_list info)
{
	if (format == 'c')
		return (ft_putchar(va_arg(info, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(info, char *)));
	else if (format == 'p')
		return (printptr(va_arg(info, void *)));
	else if (format == 'd')
		return (ft_printd(va_arg(info, int)));
	else if (format == 'i')
		return (ft_printd(va_arg(info, int)));
	else if (format == 'u')
		return (ft_printuns(va_arg(info, unsigned int)));
	else if (format == '%')
		return (ft_putchar('%'));
	else if (format == 't')
		return (ft_print_tab(va_arg(info, char **)));
	else if (format == 'x')
		return (ft_putnbr_base(va_arg(info, int), "0123456789abcdef"));
	else if (format == 'X')
		return (ft_putnbr_base(va_arg(info, int), "0123456789ABCDEF"));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	info;
	int		i;
	int		res;

	i = 0;
	res = 0;
	va_start(info, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			res += ft_triprintf(format[i], info);
		}
		else
			res += ft_putchar(format[i]);
		i++;
	}
	va_end(info);
	return (res);
}
