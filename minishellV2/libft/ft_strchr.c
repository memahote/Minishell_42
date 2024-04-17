/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:31:27 by memahote          #+#    #+#             */
/*   Updated: 2022/11/09 14:43:56 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	c1;

	i = 0;
	c1 = c;
	while (s[i])
	{
		if (s[i] == c1)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	if (s[i] == c1)
	{
		return ((char *)(s + i));
	}
	return (NULL);
}
