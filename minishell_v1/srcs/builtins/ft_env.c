/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 20:25:36 by memahote          #+#    #+#             */
/*   Updated: 2024/01/30 20:59:48 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(t_env	*env)
{
	env = ft_calloc(sizeof(t_env), 1);
	if (!env)
		return (NULL);
	return (env);
}

t_list_env	*new_var_env(char *var)
{
	t_list_env	*new_elem;
	char		*name;
	char		*value;
	int			index_name;

	index_name = ft_strchr_env(var, '=');
	new_elem = ft_calloc(sizeof(t_list_env), 1);
	if (index_name != -1)
	{
		name = ft_substr(var, 0, index_name);
		value = ft_substr(var, index_name, ft_strlen(var) - index_name);
		if (!name || !value || !new_elem)
			return (NULL);
		new_elem->name = name;
		new_elem->value = value;
	}
	else
	{
		new_elem->name = ft_strdup(var);
		new_elem->value = NULL;
	}
	new_elem->prev = NULL;
	new_elem->next = NULL;
	return (new_elem);
}

void	add_back_env(t_env *env, t_list_env *new)
{
	t_list_env	*current;

	current = env->head;
	if (!env->head)
		env->head = new;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
		new->prev = current;
	}
	env->len++;
}

t_env	*create_env(char **envp)
{
	t_env	*env;
	int		i;

	i = 0;
	env = NULL;
	env = init_env(env);
	env->envp = envp;
	while (envp[i])
	{
		add_back_env(env, new_var_env(envp[i]));
		env->len++;
		i++;
	}
	return (env);
}

int	ft_env(t_env *env, t_cmd *cmd)
{
	t_list_env *tmp;

	tmp = env->head;
	if (!cmd->args[1])
	{
		while (tmp)
		{
			if(tmp->value != NULL)
				printf("%s%s\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}	
	}
	else
	{
		ft_putstr_fd("env: Too many arguments.\n", 2);
	}
	return (EXIT_SUCCESS);
}
