/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:54:26 by memahote          #+#    #+#             */
/*   Updated: 2022/12/21 15:29:59 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_base(unsigned long nb, char *base)
{
	int		r;

	r = 0;
	if (nb >= 16)
	{
		r += ft_base(nb / 16, base);
		r += ft_base(nb % 16, base);
	}
	else
		r += ft_put_c(base[nb]);
	return (r);
}
