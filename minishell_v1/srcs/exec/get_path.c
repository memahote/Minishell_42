/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:35:01 by memahote          #+#    #+#             */
/*   Updated: 2024/01/05 22:35:01 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_from_envp(char **envp)
{
	int		i;
	int		j;
	char	*path_name;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		path_name = ft_substr(envp[i], 0, j);
		if (ft_strcomp("PATH", path_name) == 0)
		{
			free(path_name);
			return (envp[i]);
		}
		free(path_name);
		i++;
	}
	return (NULL);
}


void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

void	err_fullpath(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(":No such file or directory\n", 2);
}

char	*get_path(t_cmd *cmd, char **envp)
{
	char	**fullpath;
	char	**command;
	char	*exec_cmd;
	char	*possible_p;
	int		i;

	fullpath = ft_split(get_path_from_envp(envp), ':');
	command = cmd->args;
	if (!fullpath)
		err_fullpath(command[0]);
	if (command[0][0] == '/' || (command[0][0] == '.' && command[0][1] == '/'))
	{
		if (access(command[0], F_OK | X_OK) == -1)
			return (NULL);
		return (command[0]);
	}
	i = -1;
	while (fullpath[++i])
	{
		possible_p = ft_strjoin(fullpath[i], "/");
		exec_cmd = ft_strjoin(possible_p, command[0]);
		free(possible_p);
		if (access(exec_cmd, F_OK | X_OK) == 0)
			return (ft_free_tab(fullpath), exec_cmd);
		free(exec_cmd);
	}
	return (ft_free_tab(fullpath), NULL);
}