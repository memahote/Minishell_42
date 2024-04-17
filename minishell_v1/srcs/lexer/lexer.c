/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:30:27 by memahote          #+#    #+#             */
/*   Updated: 2023/11/29 16:30:27 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//Single Quotes
//Enclosing characters in single quotes (‘’) preserves the literal value of
// each character within the quotes. 
//A single quote may not occur between single quotes, 
//even when preceded by a backslash. '
//3.1.2.3 Guillemets doubles
//L'encadrement de caractères entre guillemets doubles ("") préserve la valeur 
// littérale de tous les caractères à l'intérieur des guillemets, à l'exception 
// de '$', '', '\'.
//($?) Expands to the exit status of the most recently executed foreground 
//pipeline.

int	get_var(t_list **tokens, char *line, enum e_state state)
{
	int	i;

	i = 1;
	if (line[i] == '?' || (line[i] >= '0' && line[i] <= '9'))
		i++;
	else
		while (ft_isalnum(line[i]) && line[i] != '\n' && line[i] != '\0')
			i++;
	if (state == IN_SQUOTE)
		add_back(tokens, new_cont(line, i, WORD, state));
	else
		add_back(tokens, new_cont(line, i, ENV, state));
	return (i);
}

int	redir(char *line, t_list **token, enum e_state *state)
{
	int	i;

	i = 0;
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
		{
			if (*state != OUTSIDE)
				add_back(token, new_cont(&line[i], 2, WORD, *state));
			else
				add_back(token, new_cont(&line[i], 2, HERE_DOC, *state));
			i += 2;
		}
		else
		{
			if (*state != OUTSIDE)
				add_back(token, new_cont(&line[i++], 1, WORD, *state));
			else
				add_back(token, new_cont(&line[i++], 1, REDIR_IN, *state));
		}
	}
	else if (line[i] == '>')
		i += redir_out(line, token, state, i);
	return (i);
}

int	redir_out(char *line, t_list **token, enum e_state *state, int i)
{
	if (line[i + 1] == '>')
	{
		if (*state != OUTSIDE)
			add_back(token, new_cont(&line[i], 2, WORD, *state));
		else
			add_back(token, new_cont(&line[i], 2, DREDIR_OUT, *state));
		i += 2;
	}
	else
	{
		if (*state != OUTSIDE)
			add_back(token, new_cont(&line[i++], 1, WORD, *state));
		else
			add_back(token, new_cont(&line[i++], 1, REDIR_OUT, *state));
	}
	return (i);
}

t_list	*lexer(char *line)
{
	int				i;
	t_list			*token;
	enum e_state	state;

	i = 0;
	token = NULL;
	state = OUTSIDE;
	while (line[i])
	{
		i += tokenizer(line, i, &state, &token);
	}
	del_space(&token);
	// del_quotes(&token);
	return (token);
}
