/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 21:45:52 by memahote          #+#    #+#             */
/*   Updated: 2023/11/29 21:45:52 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_list(t_list **list)
{
	t_list	*tmp;
	t_list	*next;

	if (!*list)
		return ;
	tmp = *list;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->content);
		free(tmp);
		tmp = next;
	}
}

t_list	*new_cont(char *content, int len, enum e_token type, enum e_state state)
{
	t_list	*new_elem;
	char	*cont;

	new_elem = malloc(sizeof(t_list));
	if (!new_elem)
		return (NULL);
	cont = ft_strndup(content, len);
	if (!cont)
		return (free(new_elem), NULL);
	new_elem -> content = cont;
	new_elem -> len = len;
	new_elem -> type = type;
	new_elem -> state = state;
	new_elem -> next = NULL;
	new_elem -> prev = NULL;
	return (new_elem);
}

void	add_back(t_list **lst, t_list *new)
{
	t_list	*current;

	current = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->prev = current;
}

void	del_space(t_list **head)
{
	t_list	*current;
	t_list	*next_node;

	current = *head;
	while (current != NULL)
	{
		next_node = current->next;
		if (current->type == 0 && current->state == 2)
		{
			if (current->prev != NULL)
				current->prev->next = current->next;
			else
				*head = current->next;
			if (current->next != NULL)
				current->next->prev = current->prev;
			free(current->content);
			free(current);
		}
		current = next_node;
	}
}

void	del_quotes(t_list **head)
{
	t_list	*current;
	t_list	*next_node;

	current = *head;
	while (current != NULL)
	{
		next_node = current->next;
		if ((current->type == 34 || current->type == 39) && current->state == 2)
		{
			if (current->prev != NULL)
				current->prev->next = current->next;
			else
				*head = current->next;
			if (current->next != NULL)
				current->next->prev = current->prev;
			free(current->content);
			free(current);
		}
		current = next_node;
	}
}