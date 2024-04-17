/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:49:42 by memahote          #+#    #+#             */
/*   Updated: 2022/11/17 18:37:25 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	lens1;
	size_t	lens2;
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	len = lens1 + lens2;
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	if (!s1 && !s2)
		return (ft_memmove(s, "", 1));
	if (s1 && !s2)
		return (ft_memmove(s, s1, lens1));
	if (!s1 && s2)
		return (ft_memmove(s, s2, lens2));
	ft_memmove (s, s1, lens1);
	ft_memmove (s + lens1, s2, lens2);
	s[len] = '\0';
	return (s);
}
