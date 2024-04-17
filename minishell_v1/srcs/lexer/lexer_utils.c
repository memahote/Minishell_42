/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 21:43:15 by memahote          #+#    #+#             */
/*   Updated: 2023/11/29 21:43:15 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	extract_word(char *str, enum e_state state, t_list **token)
{
	int	i;

	i = 0;
	while (!is_special(str[i]))
		i++;
	add_back(token, new_cont(str, i, WORD, state));
	return (i);
}

void	check_quote(char *str, t_list **token, enum e_state *state, char flag)
{
	enum e_state	quote;
	enum e_token	type;

	if (flag == 'S')
	{
		quote = IN_SQUOTE;
		type = SQUOTE;
	}
	else if (flag == 'D')
	{
		quote = IN_DQUOTE;
		type = DQUOTE;
	}
	if (*state == OUTSIDE)
	{
		add_back(token, new_cont(str, 1, type, *state));
		*state = quote;
	}
	else if (*state == quote)
	{
		*state = OUTSIDE;
		add_back(token, new_cont(str, 1, type, *state));
	}
	else
		add_back(token, new_cont(str, 1, type, *state));
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\f' || c == '\n')
		return (1);
	return (0);
}

int	is_special(char c)
{
	if (c == '|')
		return (1);
	if (c == '>')
		return (1);
	if (c == '\"')
		return (1);
	if (c == '\'')
		return (1);
	if (c == '<')
		return (1);
	if (c == '$')
		return (1);
	if (c == ' ')
		return (1);
	if (c == '\0')
		return (1);
	if (c == '\n')
		return (1);
	if (ft_isspace(c))
		return (1);
	return (0);
}

char	*ft_strndup(char *s1, int n)
{
	char	*copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char) * (n + 1));
	if (!copy)
		return (NULL);
	while (i < n && s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
