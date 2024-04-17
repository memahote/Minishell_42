/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:49:33 by memahote          #+#    #+#             */
/*   Updated: 2022/12/21 15:30:26 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_x(unsigned int nb, const char format)
{
	if (format == 'x')
		return (ft_base(nb, "0123456789abcdef"));
	return (ft_base(nb, "0123456789ABCDEF"));
}
