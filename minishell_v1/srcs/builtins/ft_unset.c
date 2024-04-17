/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 20:25:42 by memahote          #+#    #+#             */
/*   Updated: 2024/01/31 17:36:27 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env_var(t_list_env *head)
{
	t_list_env	*current;

	current = head;
	if (current->prev != NULL)
		current->prev->next = current->next;
	else
		head = current->next;
	if (current->next != NULL)
		current->next->prev = current->prev;
	free(current->name);
	free(current->value);
	free(current);
}

int	ft_unset(t_env *env, t_cmd *cmd)
{
	int 		i;
	t_list_env	*tmp;
	char		*n;
	int			index;
	
	if (!cmd->args[1])
		return (EXIT_SUCCESS);
	tmp = NULL;
	i = 1;
	while (cmd->args[i])
	{
		tmp = env->head;
		index = ft_strchr_ex(cmd->args[i], '=');
		n = ft_substr(cmd->args[i], 0, index);
		while (tmp)
		{
			if (ft_strcomp((tmp->name), n) == 0)
			{
				del_env_var(tmp);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (free(n), EXIT_SUCCESS);
}
