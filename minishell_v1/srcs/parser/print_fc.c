/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 19:51:26 by memahote          #+#    #+#             */
/*   Updated: 2023/12/28 19:58:45 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arg(char	**args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
}

void	print_tree_node(t_tree_node *cmd)
{
	int	i;

	i = 0;
	while (cmd->content->cmd->args[i])
	{
		printf("command arg[%i]: %s\n", i, cmd->content->cmd->args[i]);
		i++;
	}
	print_redir(cmd->content->cmd->redir);
}

void	print_redir(t_list_redir *redirl)
{
	while (redirl)
	{
		printf("Type redir: %d, file: %s\n", redirl->type, redirl->file);
		redirl = redirl->next;
	}
}

void	print_tree(t_tree_node *tree)
{
	if (tree->type == CMD)
	{
		printf("\n------------------------\n");
		printf("CMD Node\n");
		print_tree_node(tree);
	}
	else if (tree->type == PIPE)
	{
		print_tree(tree->content->pipe->right);
		printf("\n------------------------\n");
		printf("PIPE Node\n");
		print_tree(tree->content->pipe->left);
	}
}
