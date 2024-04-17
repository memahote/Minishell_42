/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:42:48 by memahote          #+#    #+#             */
/*   Updated: 2023/01/16 14:10:12 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_checktype(va_list arg, const char format)
{
	if (format == 'c')
		return (ft_put_c(va_arg(arg, int)));
	else if (format == 's')
		return (ft_put_s(va_arg(arg, char *)));
	else if (format == 'd' || format == 'i')
		return (ft_putd_i(va_arg(arg, int)));
	else if (format == 'p')
		return (ft_put_p(va_arg(arg, void *)));
	else if (format == 'u')
		return (ft_put_u(va_arg(arg, unsigned int)));
	else if (format == 'x' || format == 'X')
		return (ft_put_x(va_arg(arg, unsigned int), format));
	else if (format == '%')
		return (ft_put_c('%'));
	else
		return (ft_put_c(format));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list		arg;
	int			i;
	int			r;

	i = 0;
	r = 0;
	if (write(1, 0, 0) != 0)
		return (-1);
	va_start(arg, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1])
		{
			r += ft_checktype(arg, format[i + 1]);
			i++;
		}
		else if (format[i] != '%' || format[i + 1])
		{
			r += ft_put_c(format[i]);
		}
		i++;
	}
	va_end(arg);
	return (r);
}
