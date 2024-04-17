/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:38:27 by memahote          #+#    #+#             */
/*   Updated: 2023/12/15 14:38:27 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	handle_word(char *line, enum e_state *state, t_list **token)
{
	int	j;

	j = 0;
	j += extract_word(line, *state, token);
	return (j);
}

int	handle_space(char *line, t_list **token, enum e_state *state)
{
	add_back(token, new_cont(line, 1, SPACE_T, *state));
	return (1);
}

int	handle_dollar(char *line, int i, enum e_state *state, t_list **token)
{
	int	j;

	j = 0;
	if (is_special(line[i + 1]))
	{
		add_back(token, new_cont(&line[i], 1, WORD, *state));
		j = 1;
	}
	else
		j += get_var(token, &line[i], *state);
	return (j);
}

void	handle_quote(char *line, t_list **token, enum e_state *state, int i)
{
	if (line[i] == '\'')
	{
		check_quote(&line[i], token, state, 'S');
	}
	else if (line[i] == '\"')
	{
		check_quote(&line[i], token, state, 'D');
	}
}

int	tokenizer(char *line, int i, enum e_state *state, t_list **token)
{
	int	j;

	j = 0;
	if (!is_special(line[i]))
		j += handle_word(&line[i], state, token);
	else if (ft_isspace(line[i]))
		j += handle_space(&line[i], token, state);
	else if (line[i] == '$')
		j += handle_dollar(line, i, state, token);
	else if (line[i] == '|')
	{
		if (*state != OUTSIDE)
			add_back(token, new_cont(&line[i], 1, WORD, *state));
		else
			add_back(token, new_cont(&line[i], 1, PIPE_LINE, *state));
		j++;
	}
	else if (line[i] == '\'' || line[i] == '\"')
	{
		handle_quote(line, token, state, i);
		j++;
	}
	else if (line[i] == '<' || line[i] == '>')
		j += redir(&line[i], token, state);
	return (j);
}
