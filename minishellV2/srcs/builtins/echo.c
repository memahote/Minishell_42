/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:59:19 by memahote          #+#    #+#             */
/*   Updated: 2024/02/18 17:08:14 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_minishell *ms, t_cmd *curr)
{
	int	i;

	i = 0;
	g_exit_status = 0;
	if (curr->args[1] == NULL)
	{
		printf("\n");
		ft_free_all(ms, YES, YES);
	}
	if (ft_cmd_has_valid_option(curr->args) == FALSE)
		ft_free_all(ms, YES, YES);
	i = ft_get_start_index(curr->args);
	while (curr->args[++i])
	{
		ft_print_argument(curr->args[i]);
		if (curr->args[i + 1])
			printf(" ");
	}
	if (ft_get_start_index(curr->args) == 0)
		printf("\n");
	ft_free_all(ms, YES, YES);
}

int	ft_get_start_index(char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i])
	{
		if (args[i][0] != '-' || args[i][1] != 'n')
			break ;
		else if (args[i][0] == '-' && args[i][1] == 'n')
		{
			j = 2;
			while (args[i][j])
			{
				if (args[i][j] != 'n')
					return (i - 1);
				j++;
			}
		}
		i++;
	}
	return (i - 1);
}

void	ft_print_argument(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		printf("%c", s[i]);
		i++;
	}
}
