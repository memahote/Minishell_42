/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 07:17:26 by memahote          #+#    #+#             */
/*   Updated: 2023/12/28 19:29:45 by memahote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//Faire un itoa de l'exit status quand je l'aurai
char	*get_env(char *env)
{
	char	*name;

	name = ft_strdup(env + 1);
	if (ft_strcomp(name, "?") == 0)
		return ("0");
	free(name);
	name = getenv(env + 1);
	return (name);
}

int	count_args(t_list *token) // Size for malloc command + arg + redir
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE_LINE)
	{
		if (tmp->state == IN_SQUOTE || tmp->state == IN_DQUOTE)
		{
			i++;
			while (tmp && tmp->state != OUTSIDE)
			{
				tmp = tmp->next;
			}
		}
		else if (tmp->type == WORD || tmp->type == ENV)
		{
			i++;
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (i);
}

t_tree_node	*parse_pipe(t_list **token)
{
	t_tree_node	*branch;

	branch = ft_calloc(sizeof(t_tree_node), 1);
	if (!branch)
		return (NULL);
	branch->type = PIPE;
	branch->content = NULL;
	branch->content = malloc(sizeof(t_type));
	if (!branch->content)
		return (free(branch), NULL);
	branch->content->pipe = NULL;
	branch->content->pipe = malloc(sizeof(t_pipe));
	if (!branch->content->pipe)
	{
		free(branch->content);
		free(branch);
		return (NULL);
	}
	branch->content->pipe->left = NULL;
	branch->content->pipe->right = NULL;
	*token = (*token)->next;
	return (branch);
}
