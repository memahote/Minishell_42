/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:59:19 by memahote          #+#    #+#             */
/*   Updated: 2024/02/18 17:08:18 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_minishell *ms, t_cmd *cur)
{
	t_env	*env;

	env = ms->env_lst;
	if (ft_cmd_has_valid_option(cur->args) == FALSE)
		g_exit_status = 125;
	else if (cur->args[1])
		ft_builtin_error(ms, cur, E_FILE, 127);
	else
	{
		while (env)
		{
			if (env->value)
				printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
		g_exit_status = 0;
	}
	ft_free_all(ms, YES, YES);
}
