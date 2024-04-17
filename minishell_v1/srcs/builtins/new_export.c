/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 20:25:38 by memahote          #+#    #+#             */
/*   Updated: 2024/01/26 22:00:28 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchr_ex(char *s, int c)
{
	int	i;

	i = 0;
	if (c == '\0')
		return (ft_strlen(s));
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

int	check_if_exist(char *arg, t_env *env)
{
	t_list_env *tmp;
	int		index;
	char	*n;

	tmp = env->head;
	index = ft_strchr_ex(arg, '=');
	n = ft_substr(arg, 0, index);
	while (tmp)
	{
		if (ft_strcomp(tmp->name, n) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	update_value(char *arg, t_env *env)
{
	t_list_env *tmp;
	char	*n;
	int		index;

	tmp = env->head;
	index = ft_strchr_ex(arg, '=');
	n = ft_substr(arg, 0, index);
	while (tmp)
	{
		if (ft_strcomp(tmp->name, n) == 0)
		{
			free(tmp->value);
			tmp->value = ft_substr(arg, index, (ft_strlen(arg) - index));
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return(EXIT_SUCCESS);
}

int	ft_export(t_env *env, t_cmd *cmd)
{
	int i;

	i = 1;
	if (!cmd->args[1])
		return (print_sorted_env(env), EXIT_SUCCESS);
	while(cmd->args[i])
	{	
		if(!ft_isalpha(cmd->args[i][0]))
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
		}
		else if (ft_strchr_ex(cmd->args[i], '=') != -1)
		{
			if(check_if_exist(cmd->args[i], env))
				update_value(cmd->args[i], env);
			else
				add_back_env(env, new_var_env(cmd->args[i]));
		}
	i++;
	}	
	return (EXIT_SUCCESS);
}


// char	**convert_to_array(t_env *env)
// {
// 	char	**tab;
// 	t_list_env	*tmp;
// 	int		i;

// 	tab = malloc(sizeof(char *) * (env->len + 1));
// 	tmp = env->head;
// 	while (tmp)
// 	{
		
// 	}

// }
/*
 t_env contient ma liste chaine d'envrironement et un tableau d'env 
 donc quand j'export j'ajoute a ma liste chainer l'element puis je met
 a jour le tebleau d'env en convertissant ma liste en tableau
*/