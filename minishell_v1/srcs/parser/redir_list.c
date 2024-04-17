/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:32:51 by memahote          #+#    #+#             */
/*   Updated: 2023/12/18 14:32:51 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_list_redir	*new_redir_cont(char *file, enum e_token type)
{
	t_list_redir	*new_elem;

	new_elem = malloc(sizeof(t_list_redir));
	if (!new_elem)
		return (NULL);
	new_elem->file = ft_strdup(file);
	new_elem->type = type;
	new_elem->next = NULL;
	return (new_elem);
}

void	add_back_redir(t_list_redir **lst, t_list_redir *new)
{
	t_list_redir	*current;

	current = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

void	fill_redirl(t_list_redir **redir_l, t_list **token)
{
	t_list	*tmp;

	tmp = *token;
	while (tmp->type != PIPE_LINE && tmp != NULL)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT || \
		tmp->type == HERE_DOC || tmp->type == DREDIR_OUT)
		{
			add_back_redir(redir_l, new_redir_cont(tmp->next->content, \
			tmp->type));
		}
		tmp = tmp->next;
	}
}
