/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:31:24 by memahote          #+#    #+#             */
/*   Updated: 2022/11/17 18:27:18 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	d;
	size_t	s;
	size_t	t;
	size_t	n;

	if ((dest == NULL) && (size == 0))
		return (0);
	s = ft_strlen(src);
	d = ft_strlen(dest);
	if (size < d)
		return (s + size);
	i = 0;
	n = size - d;
	t = d + s;
	while (((i + 1) < n) && src[i])
	{
		dest[d + i] = src[i];
		i++;
	}
	dest[d + i] = '\0';
	return (t);
}
