/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:14:03 by memahote          #+#    #+#             */
/*   Updated: 2022/11/18 13:03:40 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	inset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s1c;
	size_t	start;
	size_t	end;

	if (!set)
		return (NULL);
	if (!s1)
		return ((char *)s1);
	start = 0;
	end = ft_strlen(s1);
	while (inset(s1[start], set))
		start++;
	if (start == ft_strlen(s1))
	{
		s1c = malloc(sizeof(char) * 1);
		if (!s1c)
			return (NULL);
		s1c[0] = '\0';
		return (s1c);
	}
	while (inset(s1[end - 1], set))
		end--;
	return (ft_substr(s1, start, end - start));
}
