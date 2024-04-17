/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:19:57 by memahote          #+#    #+#             */
/*   Updated: 2023/12/03 14:19:57 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_pipe_syntaxe(t_list **token)
{
	t_list	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == PIPE_LINE)
		{
			if (tmp->prev == NULL || tmp->next == NULL || \
				tmp->prev->type != -1 || tmp->next->type != -1)
			{
				ft_putstr_fd("syntax error near unexpected token `|' .\n", 2);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

char	*is_redir(enum e_token type)
{
	if (type == REDIR_IN)
		return ("<");
	else if (type == REDIR_OUT)
		return (">");
	else if (type == HERE_DOC)
		return ("<<");
	else if (type == DREDIR_OUT)
		return (">>");
	else
		return (NULL);
}

int	check_redir_syntax(t_list **token)
{
	t_list	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (is_redir(tmp->type) != NULL)
		{
			if (tmp->next == NULL || tmp->next->type != -1)
			{
				ft_putstr_fd("syntax error near unexpected token '", 2);
				ft_putstr_fd(is_redir(tmp->type), 2);
				ft_putstr_fd("'.\n", 2);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int	check_syntax(t_list **token)
{
	if (!check_pipe_syntaxe(token) || !check_redir_syntax(token))
		return (1);
	else
		return (0);
}