/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 20:25:38 by memahote          #+#    #+#             */
/*   Updated: 2024/01/31 18:01:02 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//export test="saluttoi$HOME/dsfsdf" -> A Gerer
// export $PWD$HOME -> erreur a gerer

// int	found_in_env(t_list_env **env, char *arg)
// {
// 	t_list_env *tmp;
// 	char		*cible;

// 	tmp = (*env);
// 	while (tmp)
// 	{
// 		cible = ft_strchr(tmp->value, '=');
// 		printf("############### 1 1 1%s\n", tmp->value);
// 		printf("###############%s\n", (tmp->value - ft_strlen(cible)));
// 		if (ft_strnstr(cible, arg, ft_strlen(cible)) != NULL)
// 			return (1);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// int	ft_export(t_list_env **env, t_cmd *cmd)
// {
// 	t_env	*new_env;

// 	new_env = NULL;
// 	new_env = create_env(*env->envp);
// 	if (!cmd->args[1])
// 		return (print_env_sort(env), EXIT_SUCCESS);
// 	else
// 	{
// 		if(!ft_isalpha(cmd->args[1][0]))
// 		{
// 			ft_putstr_fd("export: ", 2);
// 			ft_putstr_fd(cmd->args[1], 2);
// 			ft_putstr_fd(": not a valid identifier\n", 2);
// 			return(EXIT_FAILURE);
// 		}
		
		
// 	}
	// while (cmd->args[i])
	// {
	// 	if (!ft_isdigit(cmd->args[i][0]))
	// 	{
	// 		if(strchr(cmd->args[i], '=') != NULL && !cmd->args[i + 1])
	// 			add_back_env(env, new_var_env(cmd->args[i]));
	// 		else if (strchr(cmd->args[i], '=') != NULL && 
	// 		strchr(cmd->args[i + 1], '=') == NULL)
	// 		{
	// 			if (found_in_env(env, cmd->args[i + 1]))
	// 			{
	// 				cmd->args[i] = ft_strjoin(cmd->args[i], cmd->args[i + 1]);
	// 				add_back_env(env, new_var_env(cmd->args[i]));
	// 				i++;
	// 			}
	// 		}
	// 		else if (strchr(cmd->args[i], '=') != NULL)
	// 			add_back_env(env, new_var_env(cmd->args[i]));
	// 	}
	// 	else
	// 	{
	// 		ft_putstr_fd("export: ", 2);
	// 		ft_putstr_fd(cmd->args[i], 2);
	// 		ft_putstr_fd(": not a valid identifier\n", 2);
	// 	}
	// 	i++;
	// }
	// return (EXIT_SUCCESS);
// }


// //idee a voir faire un split de = pour avoir les key et value

// Export -> ajoute a la liste chaine de env le name + value et update 
// char ** de t_env pour execve car il prend un char **;