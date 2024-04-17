/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:12:37 by memahote          #+#    #+#             */
/*   Updated: 2022/11/17 18:28:45 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	char	*str;
	int		len;

	ch = c;
	str = (char *)s;
	len = ft_strlen(str);
	if (ch == 0)
		return (&str[len]);
	while (str[len] != ch)
	{
		if (len == 0)
			return (NULL);
		len --;
	}
	return (&str[len]);
}
