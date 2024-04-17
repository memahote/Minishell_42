/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:55:54 by itouil            #+#    #+#             */
/*   Updated: 2024/02/18 16:12:37 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_has_redir(t_cmd *curr)
{
	if (curr->f_redin[0])
		return (YES);
	if (curr->f_redout[0])
		return (YES);
	return (NO);
}

void	ft_handle_redir(t_minishell *m, t_cmd *c)
{
	int	i;

	i = -1;
	while (c->f_redin[++i])
	{
		g_exit_status = 0;
		if (c->t_redin[i] == T_FILE_IN)
			c->fd_in = ft_open_fd(m, c, c->f_redin[i], c->t_redin[i]);
		else if (c->t_redin[i] == T_HEREDOC)
			c->fd_in = ft_handle_heredoc(m, c->f_redin[i]);
	}
	i = -1;
	while (c->f_redout[++i])
	{
		g_exit_status = 0;
		c->fd_out = ft_open_fd(m, c, c->f_redout[i], c->t_redout[i]);
	}
	if (ft_is_forkable(m, NO) == TRUE)
	{
		if (dup2(c->fd_in, STDIN_FILENO) == -1)
			ft_perror(m, E_DUP2, YES, NULL);
		if (dup2(c->fd_out, STDOUT_FILENO) == -1)
			ft_perror(m, E_DUP2, YES, NULL);
	}
}

int	ft_open_fd(t_minishell *m, t_cmd *c, char *filename, t_type filetype)
{
	int		fd;

	fd = 0;
	if (filetype == T_FILE_IN)
		fd = open(filename, O_RDONLY);
	else if (filetype == T_FILE_TR)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (filetype == T_FILE_AP)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		g_exit_status = 1;
		m->file_error = YES;
		if (ft_perror_fd(c, filename, filetype) != 0)
			return (0);
		if (m->n_pipes > 0)
			ft_free_pipes(m);
		if (ft_is_forkable(m, NO) == TRUE)
			ft_perror(m, NULL, YES, NULL);
		else if (ft_is_forkable(m, NO) == FALSE)
			ft_perror(m, NULL, NO, NULL);
	}
	return (fd);
}

int	ft_perror_fd(t_cmd *c, char *filename, t_type filetype)
{
	if (ft_strlen(filename) == 0)
	{
		printf("minishell: ambiguous redirect\n");
		if (!c)
			return (42);
		return (0);
	}
	if (filetype == T_FILE_IN)
	{
		if (!c)
			return (printf("minishell: %s: %s\n", filename, E_FILE));
		else
			printf("minishell: %s: %s\n", filename, E_FILE);
	}
	else if (filetype == T_FILE_TR || filetype == T_FILE_AP)
	{
		if (!c)
			return (printf("minishell: %s: %s\n", filename, E_DIR));
		else
			printf("minishell: %s: %s\n", filename, E_DIR);
	}
	return (0);
}

void	ft_close_fds(t_cmd *curr)
{
	if (curr->fd_in > STDIN_FILENO)
		close(curr->fd_in);
	if (curr->fd_out > STDOUT_FILENO)
		close(curr->fd_out);
	curr->fd_in = STDIN_FILENO;
	curr->fd_out = STDOUT_FILENO;
}
