/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:06:04 by memahote          #+#    #+#             */
/*   Updated: 2022/11/17 18:34:58 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*st;
	int		len;
	int		i;

	len = ft_strlen(s1) + 1;
	i = 0;
	st = malloc(sizeof(char) * len);
	if (!st)
		return (NULL);
	while (s1[i])
	{
		st[i] = s1[i];
		i++;
	}
	st[i] = '\0';
	return (st);
}
