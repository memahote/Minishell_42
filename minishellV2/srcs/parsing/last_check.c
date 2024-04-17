/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:32:51 by memahote          #+#    #+#             */
/*   Updated: 2024/02/18 17:09:59 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_last_check(t_minishell *ms)
{
	t_token	*curr;

	curr = ms->token_lst;
	while (curr)
	{
		if (curr->type == T_OTHER)
			curr->type = T_COMMAND;
		else if (curr->type == T_REDIR_IN)
			curr->next->type = T_FILE_IN;
		else if (curr->type == T_REDIR_OUT)
			curr->next->type = T_FILE_TR;
		else if (curr->type == T_REDIR2_OUT)
			curr->next->type = T_FILE_AP;
		else if (curr->type == T_REDIR2_IN)
			curr->next->type = T_HEREDOC;
		curr = curr->next;
	}
	if (ft_check_arg(ms) == EXIT_NO_CMD)
		return (EXIT_NO_CMD);
	return (EXIT_SUCCESS);
}

int	ft_check_arg(t_minishell *ms)
{
	int		n_args;
	t_token	*curr;
	t_token	*first_cmd;

	n_args = 0;
	curr = ms->token_lst;
	while (curr)
	{
		n_args = 0;
		first_cmd = curr;
		while (curr->next && curr->type != T_PIPE)
		{
			if (curr->type == T_COMMAND)
				n_args++;
			curr = curr->next;
		}
		if (curr->type == T_COMMAND)
			n_args++;
		if (ft_check_redir(ms, first_cmd, n_args) == EXIT_NO_CMD)
			return (EXIT_NO_CMD);
		if (ft_check_redir(ms, first_cmd, n_args) == EXIT_SUCCESS)
			ft_add_cmd_back(&ms->cmd_lst, ft_new_cmd(first_cmd, n_args));
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_open_and_close(t_minishell *m, t_cmd *c, char *filename, t_type filetype)
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
	if (fd)
		close(fd);
	return (0);
}

int	ft_check_redir(t_minishell *ms, t_token *first, int n_args)
{
	t_token	*curr;

	curr = first;
	if (n_args == 0)
	{
		if (first->type == T_EMPTY
			&& (!first->next || first->next->type == T_PIPE))
			return (EXIT_NO_CMD);
		while (curr)
		{
			if (curr->type == T_EMPTY && curr->next)
				curr = curr->next;
			if (curr->type == T_FILE_IN || curr->type == T_FILE_TR || \
				curr->type == T_FILE_AP)
				ft_open_and_close(ms, NULL, curr->content, curr->type);
			if (curr->type == T_HEREDOC)
				ft_handle_heredoc(ms, curr->content);
			curr = curr->next;
		}
		if (ms->n_pipes > 0)
			return (GO_NEXT);
		return (EXIT_NO_CMD);
	}
	return (EXIT_SUCCESS);
}
