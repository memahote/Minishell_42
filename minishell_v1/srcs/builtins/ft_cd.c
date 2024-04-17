/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 20:25:31 by memahote          #+#    #+#             */
/*   Updated: 2024/01/31 18:00:25 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_home(char *arg)
{
	if (!arg)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (EXIT_SUCCESS);
	}
	if(ft_strcomp(arg, "HOME"))
	{
		ft_putstr_fd("cd: HOME: No such file or directory\n", 2);
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}


int	ft_cd(t_cmd *cmd)
{
	char	*home_path;

	home_path = get_env("$HOME");
	if (cmd->nb_args > 2)
		return (ft_putstr_fd("cd: too many arguments\n", 2), EXIT_SUCCESS);
	if (cmd->nb_args == 1 )
	{
		if(chdir(home_path) != 0)
			err_home(cmd->args[1]);
	}
	else
	{
		if(chdir(cmd->args[1]) != 0)
		{
			ft_putstr_fd(cmd->args[1], 2);
			perror(" ");
		}
	}
	return (EXIT_SUCCESS);
}
