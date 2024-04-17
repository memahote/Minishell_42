/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:59:19 by memahote          #+#    #+#             */
/*   Updated: 2023/12/17 15:59:19 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

int	is_redir_2(enum e_token type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == DREDIR_OUT || type == HERE_DOC);
}

char	*parse_quotes(char *args, t_list **token)
{
	char	*tmp;
	char	*tmp_env;

	tmp = NULL;
	tmp_env = NULL;
	while ((*token) && (*token)->state != OUTSIDE)
	{
		tmp = args;
		if ((*token)->type == ENV && (*token)->state == IN_DQUOTE)
		{
			tmp_env = get_env((*token)->content);
			if (tmp_env != NULL)
				args = ft_strjoin(args, tmp_env);
		}
		else
			args = ft_strjoin(args, (*token)->content);
		free(tmp);
		(*token) = (*token)->next;
	}
	return (args);
}


int	fill_cmd(t_list **token, char **args, t_list_redir **redir_l)
{
	int	i;

	i = 0;
	while ((*token) && (*token)->type != PIPE_LINE)
	{
		if ((*token)->type == WORD && (*token)->state == OUTSIDE)
			args[i++] = ft_strndup((*token)->content, (*token)->len);
		else if ((*token)->state == IN_DQUOTE || (*token)->state == IN_SQUOTE)
		{
			args[i] = ft_strdup("");
			args[i] = parse_quotes(args[i], token);
			i++;
		}
		else if (is_redir_2((*token)->type))
		{
			add_back_redir(redir_l, new_redir_cont((*token)->next->content, \
			(*token)->type));
			(*token) = (*token)->next;
		}
		else if ((*token)->type == ENV)
		{
			args[i] = get_env((*token)->content);
			if (args[i])
				i++;
		}
		if ((*token))
			(*token) = (*token)->next;
	}
	return (args[i] = NULL, EXIT_SUCCESS);
}

t_tree_node	*parser_cmd(t_list **token, char **env)
{
	t_tree_node		*new;
	char			**args;
	int				nb_args;
	t_list_redir	*redir_l;

	redir_l = NULL;
	nb_args = count_args(*token);
	args = malloc(sizeof(char *) * (nb_args + 1));
	if (!args)
		return (NULL);
	if (fill_cmd(token, args, &redir_l) == EXIT_FAILURE)
		return (NULL);
	new = new_cmd(args, redir_l, env, nb_args);
	return (new);
}

int	parser(t_tree **tree, t_list *token, char **env)
{
	t_tree_node	*tree_node;

	tree_node = NULL;
	if (!token)
		return (EXIT_FAILURE);
	tree_node = parser_cmd(&token, env);
	if (!tree_node)
		return (EXIT_FAILURE);
	if (!(*tree)->tree_root)
		(*tree)->tree_root = tree_node;
	else
	{
		if (!(*tree)->tree_root->content->pipe->right)
			(*tree)->tree_root->content->pipe->right = tree_node;
		else
			(*tree)->tree_root->content->pipe->left = tree_node;
	}
	if (token && token->type == PIPE_LINE)
	{
		tree_node = parse_pipe(&token);
		tree_node->content->pipe->right = (*tree)->tree_root;
		(*tree)->tree_root = tree_node;
	}
	parser(tree, token, env);
	return (EXIT_SUCCESS);
}
