/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:20:02 by memahote          #+#    #+#             */
/*   Updated: 2024/01/18 19:20:02 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_fd_execve(t_cmd *cmd, int fd[2])
{
	if (cmd->fd_in != 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
		if (fd[0] != 0)
			close(fd[0]);
	}
	if (cmd->fd_out != 1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
		if (fd[1] != 1)
			close(fd[1]);
	}
}

int	execute_cmd(t_cmd *cmd, char **env, int fd[2])
{
	char	*cm;
	int		pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		if (cmd->redir)
		{
			do_redir(cmd->redir, &cmd->fd_in, &cmd->fd_out);
			if (cmd->fd_in == -1)
				exit(1);
		}
		check_fd_execve(cmd, fd);
		cm = get_path(cmd, env);
		if (cm)
			execve(cm, cmd->args, env);
	}
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	return (pid);
}