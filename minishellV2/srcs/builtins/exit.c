/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 15:59:19 by memahote          #+#    #+#             */
/*   Updated: 2024/02/18 17:08:26 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_minishell *ms, t_cmd *curr)
{
	if (ms->n_pipes == 0)
		printf("exit\n");
	if (curr->args[1] && ft_isnum(curr->args[1]) == 1 && curr->args[2])
		return (ft_builtin_error(ms, curr, E_ARGS, 1));
	if (curr->args[1] && ft_isnum(curr->args[1]) == 0)
	{
		ft_builtin_error(ms, curr, curr->args[1], 2);
		ft_free_all(ms, YES, YES);
	}
	if (curr->args[1] && ft_isnum(curr->args[1]) == 1)
	{
		g_exit_status = ft_atoi(curr->args[1]);
		ft_free_all(ms, YES, YES);
	}
	if (curr->has_heredoc == 1)
		unlink(".heredoc");
	ft_free_all(ms, YES, YES);
}

int	ft_isnum(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[1] && (s[i] == '-' || s[i] == '+'))
		{
			if (i != 0)
				return (0);
			i++;
		}
		if (ft_isdigit(s[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
