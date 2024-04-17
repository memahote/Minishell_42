/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:24:44 by memahote          #+#    #+#             */
/*   Updated: 2022/12/19 14:30:54 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_extract(char *str)
{
	int		i;
	char	*s;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		return (s[i] = '\n', s[i + 1] = '\0', s);
	return (s[i] = '\0', s);
}

char	*ft_reset(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\0')
		return (free(str), str = NULL, NULL);
	if (str[i] == '\n')
		i++;
	new = malloc(sizeof(char) * ((ft_strlen(str) - i) + 1));
	if (!new)
		return (free(str), str = NULL, NULL);
	j = 0;
	while (str[i])
	{
		new[j] = str[i];
		j++;
		i++;
	}
	new[j] = '\0';
	return (free(str), str = NULL, new);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (!s1)
			return (free (s1), s1 = NULL, NULL);
		s1[0] = '\0';
	}
	s = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (free (s1), s1 = NULL, NULL);
	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		s[i++] = s2[j++];
	return (s[i] = 0, free(s1), s1 = NULL, s);
}

int	ft_strlen_gnl(char *s)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (s[i])
		while (s[i])
			i++;
	return (i);
}
