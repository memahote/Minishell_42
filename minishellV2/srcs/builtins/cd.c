/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:00 by memahote          #+#    #+#             */
/*   Updated: 2024/02/18 17:08:06 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_minishell *ms, t_cmd *curr)
{
	char	cur_dir[200];
	int		arg_flag;
	char	*tmp_dir;

	arg_flag = 0;
	getcwd(cur_dir, sizeof(cur_dir));
	if (!ft_cmd_has_valid_option(curr->args))
		return (ft_builtin_error(ms, curr, NULL, 2));
	if (curr->args[1] && curr->args[2])
		return (ft_builtin_error(ms, curr, E_ARGS, 1));
	arg_flag = ft_cd_arg(ms, curr, arg_flag);
	if (arg_flag == -1)
		return (ft_builtin_error(ms, curr, E_FILE, 1));
	if (arg_flag == 1)
		return (ft_builtin_error(ms, curr, E_HOME, 1));
	tmp_dir = ft_strdup(cur_dir);
	ft_update_env(&ms->env_lst, "OLDPWD", tmp_dir);
	getcwd(cur_dir, sizeof(cur_dir));
	tmp_dir = ft_strdup(cur_dir);
	ft_update_env(&ms->env_lst, "PWD", tmp_dir);
	if (!ft_find_env(ms->env_lst, "PWD"))
		free(tmp_dir);
	g_exit_status = 0;
	if (ms->n_pipes > 0)
		ft_free_all(ms, YES, YES);
}

int	ft_cd_arg(t_minishell *ms, t_cmd *curr, int arg_flag)
{
	if (curr->args[1])
	{
		if (ft_strlen(curr->args[1]) == 1 && curr->args[1][0] == '~')
			arg_flag = chdir(ft_find_env(ms->env_lst, "HOME"));
		else
			arg_flag = chdir(curr->args[1]);
	}
	else
	{
		arg_flag = chdir(ft_find_env(ms->env_lst, "HOME"));
		if (arg_flag < 0)
			return (1);
	}
	return (arg_flag);
}
