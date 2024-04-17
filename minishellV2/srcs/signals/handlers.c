/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:55:54 by itouil            #+#    #+#             */
/*   Updated: 2024/02/13 18:49:20 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_heredoc(int signum, t_minishell *ms)
{
	static t_minishell	*h;

	if (!signum && ms)
	{
		h = ms;
		return ;
	}
	if (signum == SIGINT)
	{
		if (h->n_pipes > 0)
			ft_free_all(h, YES, YES);
		else
			ft_free_all(h, NO, YES);
	}
}

void	ft_handler_sigint(int signum)
{
	if (signum != SIGINT)
		return ;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 130;
}

void	ft_handler_heredoc(int signum)
{
	g_exit_status = 130;
	ft_free_heredoc(signum, NULL);
}

void	ft_handler_child(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		return ;
	}
	else if (signum == SIGQUIT)
		g_exit_status = 128 + signum;
}
