/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 20:25:34 by memahote          #+#    #+#             */
/*   Updated: 2024/01/01 05:14:59 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmd *cmd, int fd_out)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (cmd->args[i] && cmd->args[i][0] == '-' && cmd->args[i][1] == 'n')
	{
		n = 1;
		while (cmd->args[i] && cmd->args[i][0] == '-' && cmd->args[i][1] == 'n')
			i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], fd_out);
		i++;
		if (cmd->args[i])
			ft_putchar_fd(' ', fd_out);
	}
	if (n == 0)
		ft_putchar_fd('\n', fd_out);
	return (EXIT_SUCCESS);
}
