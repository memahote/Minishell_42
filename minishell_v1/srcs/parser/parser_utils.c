/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:06:19 by memahote          #+#    #+#             */
/*   Updated: 2024/01/19 22:48:42 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*init_tree(t_tree *tree)
{
	tree = malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->tree_root = NULL;
	return (tree);
}

t_tree_node	*new_cmd(char **args, t_list_redir *redir, char **env, int len)
{
	t_tree_node	*node;

	node = malloc(sizeof(t_tree_node));
	node->content = malloc(sizeof(t_type));
	node->content->cmd = malloc(sizeof(t_cmd));
	if (!node || !node->content || !node->content->cmd)
		return (NULL);
	node->type = CMD;
	node->content->cmd->args = args;
	node->content->cmd->nb_args = len;
	node->content->cmd->env = env;
	node->content->cmd->redir = redir;
	node->content->cmd->fd_in = 0;
	node->content->cmd->fd_out = 1;
	return (node);
}

void	free_redir_list(t_list_redir *list)
{
	t_list_redir	*next_node;

	while (list)
	{
		next_node = list->next;
		free(list->file);
		free(list);
		list = next_node;
	}
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	free_redir_list(cmd->redir);
	free(cmd);
}

void	free_tree(t_tree_node *node)
{
	if (node->type == CMD)
	{
		free_cmd(node->content->cmd);
		free(node->content);
		free(node);
	}
	else if (node->type == PIPE)
	{
		free_tree(node->content->pipe->right);
		free_tree(node->content->pipe->left);
		free(node->content->pipe);
		free(node->content);
		free(node);
	}
}
