/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:37:23 by memahote          #+#    #+#             */
/*   Updated: 2024/02/19 17:23:08 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	main(int ac, char **av, char **envp)
{
	t_minishell	ms;

	(void)ac;
	if (av[1])
	{
		printf("minishell: %s: no such file or directory\n", av[1]);
		return (1);
	}
	ft_bzero(&ms, sizeof(t_minishell));
	ms.envp = envp;
	ft_init_env_lst(&ms.env_lst, ms.envp);
	ms.paths = ft_get_paths(ms.env_lst);
	ft_main_loop(&ms);
}

void	ft_main_loop(t_minishell *ms)
{
	while (42)
	{
		ft_signals();
		ms->input = readline("minishell> ");
		if (ms->input == NULL)
			ft_free_all(ms, NO, YES);
		add_history(ms->input);
		if (ft_everything_is_space(ms->input) == FALSE)
		{
			ms->n_pipes = 0;
			ms->file_error = 0;
			if (ft_parser(ms, ms->input) == EXIT_SUCCESS)
			{
				ft_signals_child(ms);
				ft_executer(ms);
				if (ms->n_pipes > 0)
					ft_free_pipes(ms);
				unlink(".heredoc");
			}
			ft_free_all(ms, NO, NO);
		}
	}
	rl_clear_history();
}

void	ft_free_all(t_minishell *ms, int free_pipes, int exit_flag)
{
	if (ms->input == NULL)
		printf("exit\n");
	free(ms->input);
	ft_free_token_lst(&ms->token_lst);
	ft_free_cmd_lst(&ms->cmd_lst);
	if (free_pipes == YES && ms->n_pipes > 0)
		ft_free_pipes(ms);
	if (exit_flag == YES)
	{
		ft_free_env_lst(&ms->env_lst);
		ft_free_str_array(ms->paths);
		exit (g_exit_status);
	}
}
