/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:45:06 by memahote          #+#    #+#             */
/*   Updated: 2024/01/24 19:45:06 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_redir(t_list_redir *list, int *fd_in, int *fd_out)
{
	t_list_redir *tmp;

	tmp = list;
	while(tmp)
	{
		if (tmp->type == REDIR_IN)
		{
			if (access(tmp->file, F_OK) == 0)
			{
				close(*fd_in);
				*fd_in = open(tmp->file, O_RDONLY, 0666);
			}
			else
			{
				*fd_in = -1;
				write(2, "minishell: ", 11);
				ft_putstr_fd(tmp->file, 2);
				ft_putstr_fd(": No such file or directory", 2);
			}
		}
		else if (tmp->type == REDIR_OUT)
		{
			close(*fd_out);
			*fd_out =  open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		}
		else if (tmp->type == DREDIR_OUT)
		{
			close(*fd_out);
			*fd_out = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		}
		else if (tmp->type == HERE_DOC)
		{
			close(*fd_in);
			*fd_in = open(tmp->file, O_RDONLY, 0666);
		}
		tmp = tmp->next;
	}
}