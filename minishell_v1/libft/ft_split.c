/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:45:22 by memahote          #+#    #+#             */
/*   Updated: 2022/11/18 13:04:39 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	clear(char **strs, int a)
{
	if (!strs[a])
	{
		while (a >= 0)
		{
			free(strs[a]);
			a--;
		}
		free(strs);
		return (1);
	}
	return (0);
}

int	ft_wordcount(char const *s, char c)
{
	int	wordcount;
	int	i;

	wordcount = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			while (s[i] == c)
				i++;
		else
		{
			while (s[i] && s[i] != c)
				i++;
			wordcount++;
		}
	}
	return (wordcount);
}

static	char	**tab(char const *s, char **strs, char c, unsigned int begin)
{
	size_t	end;
	int		wordcount;

	end = 0;
	wordcount = 0;
	while (s[begin])
	{
		if (s[begin] == c)
			while (s[begin] == c)
				begin++;
		else
		{
			end = begin;
			while (s[end] && s[end] != c)
				end++;
			strs[wordcount] = ft_substr(s, begin, (end - begin));
			if (wordcount < ft_wordcount(s, c) && clear (strs, wordcount))
				return (NULL);
			wordcount++;
			begin = end;
		}
	}
	strs[wordcount] = 0;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		wordcount;

	if (!s)
		return (0);
	wordcount = ft_wordcount(s, c);
	strs = malloc(sizeof(char *) * (wordcount + 1));
	if (!strs)
		return (NULL);
	return (tab(s, strs, c, 0));
}
