/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:39:26 by memahote          #+#    #+#             */
/*   Updated: 2022/11/17 18:25:54 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dest;
	char	*sr;
	size_t	i;

	dest = (char *)dst;
	sr = (char *)src;
	i = -1;
	if (dest < sr)
		while (++i < len)
			dest[i] = sr[i];
	else if (dest > sr)
	{
		while (len > 0)
		{
			dest[len - 1] = sr[len - 1];
			len--;
		}
	}
	return (dest);
}
