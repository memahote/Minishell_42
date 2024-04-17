/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:38:27 by memahote          #+#    #+#             */
/*   Updated: 2022/11/18 17:44:45 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*news;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	else if (len > ft_strlen(s + start))
		news = malloc(sizeof(char) * (ft_strlen(&s[start]) + 1));
	else
		news = malloc(sizeof(char) * (len + 1));
	if (!news)
		return (NULL);
	while (s[start] && i < len)
	{
		news[i] = s[start];
		i++;
		start++;
	}
	news[i] = '\0';
	return (news);
}
