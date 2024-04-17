/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_nothing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 04:38:12 by memahote          #+#    #+#             */
/*   Updated: 2024/01/26 22:21:55 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_swap(t_list_env *a, t_list_env *b)
{
	char	*name_tmp;
	char	*val_tmp;

	name_tmp = a->name;
	val_tmp = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = name_tmp;
	b->value = val_tmp;
}

void	ft_sort(t_env *env)
{
	t_list_env	*current;

	current = env->head;
	while (current->next)
	{
		if (ft_strcmp(current->name, current->next->name) > 0)
		{
			ft_swap(current, current->next);
			current = env->head;
		}
		else
			current = current->next;
	}
}

void	print_sorted_env(t_env *env)
{
	t_env		*tmp;
	t_list_env	*current;

	tmp = env;
	ft_sort(tmp);
	current = tmp->head;
	while (current)
	{
		printf("declare -x %s", current->name);
		if (current->value)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}
