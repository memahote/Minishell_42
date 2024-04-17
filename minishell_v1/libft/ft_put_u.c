/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:52:22 by memahote          #+#    #+#             */
/*   Updated: 2022/12/21 15:30:24 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_u(unsigned int nb)
{
	int		r;

	r = 0;
	if (nb >= 10)
	{
		r += ft_put_u(nb / 10);
		r += ft_put_u(nb % 10);
	}
	else
		r += ft_put_c(nb + '0');
	return (r);
}
