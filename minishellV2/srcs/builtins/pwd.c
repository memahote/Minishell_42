/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:59:19 by memahote          #+#    #+#             */
/*   Updated: 2024/02/18 17:08:41 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_minishell *ms, t_cmd *curr)
{
	char	pwd[4096];

	if (ft_cmd_has_valid_option(curr->args) == FALSE)
		ft_free_all(ms, YES, YES);
	if (getcwd(pwd, sizeof(pwd)))
		printf("%s\n", pwd);
	g_exit_status = 0;
	ft_free_all(ms, YES, YES);
}
