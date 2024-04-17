/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:52:02 by memahote          #+#    #+#             */
/*   Updated: 2022/12/21 15:30:18 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_p(void *p)
{
	int				r;
	unsigned long	p2;

	p2 = (unsigned long)p;
	r = 0;
	r += ft_put_s("0x");
	r += ft_base(p2, "0123456789abcdef");
	return (r);
}
