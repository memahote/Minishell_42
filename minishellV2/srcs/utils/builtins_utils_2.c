/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:37:39 by cacarval          #+#    #+#             */
/*   Updated: 2024/02/18 17:10:52 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_args_are_valid(char *arg, int export_flag)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalpha(arg[0]) || (ft_isalnum(arg[i]) == 0 && arg[i] != '_'))
		{
			dup2(STDERR_FILENO, STDOUT_FILENO);
			if (export_flag == YES)
				printf("minishell: export: '%s': %s\n", arg, E_EXPORT);
			g_exit_status = 1;
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	ft_if_no_path(t_minishell *ms, t_cmd *curr, char *cmd)
{
	if (ft_find_env(ms->env_lst, "PATH") == NULL)
	{
		if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		{
			if (access(cmd, F_OK | X_OK) == 0)
				execve(cmd, curr->args, ms->envp);
			ft_free_str_array(ms->envp);
			ft_perror(ms, E_CMD, YES, cmd);
		}
		else
		{
			ft_free_str_array(ms->envp);
			ft_perror(ms, E_FILE, YES, cmd);
		}
	}
}

void	ft_build_envp(t_minishell *ms)
{
	int		i;
	char	*tmp;
	t_env	*env;

	i = 0;
	env = ms->env_lst;
	while (env)
	{
		i++;
		env = env->next;
	}
	ms->envp = ft_calloc(sizeof(char *), (i + 1));
	if (!ms->envp)
		ft_free_all(ms, YES, YES);
	i = 0;
	env = ms->env_lst;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		ms->envp[i] = ft_strjoin(tmp, env->value);
		free(tmp);
		i++;
		env = env->next;
	}
}
