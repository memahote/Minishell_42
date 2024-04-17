/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:07:53 by memahote          #+#    #+#             */
/*   Updated: 2024/01/03 22:07:53 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(char	*arg)
{
	if (!arg)
		return (0);
	if (ft_strcomp(arg, "cd") == 0)
		return (1);
	else if (ft_strcomp(arg, "echo") == 0)
		return (2);
	else if (ft_strcomp(arg, "env") == 0)
		return (3);
	else if (ft_strcomp(arg, "exit") == 0)
		return (4);
	else if (ft_strcomp(arg, "pwd") == 0)
		return (5);
	else if (ft_strcomp(arg, "export") == 0)
		return (6);
	else if (ft_strcomp(arg, "unset") == 0)
		return (7);
	else
		return (0);
}

void	which_builtins(t_cmd *cmd, t_env *env, int builtins)
{
	if (builtins == 1)
		ft_cd(cmd);
	else if (builtins == 2)
		ft_echo(cmd, 1);
	else if (builtins == 5)
		ft_pwd();
	else if (builtins == 3)
		ft_env(env, cmd);
	// else if (builtins == 4)
	// 	;// ft_exit(cmd, 1);
	else if (builtins == 6)
		ft_export(env, cmd);
	else if (builtins == 7)
		ft_unset(env, cmd);
}

int	which_exec(t_tree_node *node, t_env *env, int p_fd[2])
{
	int	builtins;
	int pid;

	builtins = check_builtins(node->content->cmd->args[0]);
	pid = 0;
	if (builtins > 0)
	{
		which_builtins(node->content->cmd, env, builtins);
		// print_env(env->head);
	}
	else
		pid = execute_cmd(node->content->cmd, env->envp, p_fd);
	return (pid);
}

int	*find_right_left(t_tree_node *node)
{
	return (&node->content->pipe->right->content-> \
		pipe->left->content->cmd->fd_out);
}

void	update_fd(int *old, int new)
{
	*old = new;
}

void execute_tree(t_tree_node *node, t_env *env)
{
    int p_fd[2];
    int pid;

    if (node->type == CMD)
    {
        pid = which_exec(node, env, p_fd);
    }
    else if (node->type == PIPE)
    {
        if (pipe(p_fd) < 0)
            return;

        if (node->content->pipe->right->type == CMD)
            update_fd(&node->content->pipe->right->content->cmd->fd_out, p_fd[1]);
        else if (node->content->pipe->right->type == PIPE)
            update_fd(find_right_left(node), p_fd[1]);
         update_fd(&node->content->pipe->left->content->cmd->fd_in, p_fd[0]);
        execute_tree(node->content->pipe->right, env);
        execute_tree(node->content->pipe->left, env);
        close(p_fd[0]);
		close(p_fd[1]);
    }
        waitpid(pid, NULL, 0);
}


// printf("right : %s\n", node->content->pipe->right->content->cmd->args[0]);
        // printf("left : %s\n", node->content->pipe->left->content->cmd->args[0]);
        // printf("right right: %s\n", node->content->pipe->right->content->pipe->right->content->cmd->args[0]);
        // printf("right left: %s\n", node->content->pipe->right->content->pipe->left->content->cmd->args[0]);
        // printf("right right righ: %s\n", node->content->pipe->right->content->pipe->right->content->pipe->right->content->cmd->args[0]);
        // printf("right right left: %s\n", node->content->pipe->right->content->pipe->right->content->pipe->left->content->cmd->args[0]);
        // printf("right right righ right: %s\n", node->content->pipe->right->content->pipe->right->content->pipe->right->content->pipe->right->content->cmd->args[0]);
        // printf("right right righ left: %s\n", node->content->pipe->right->content->pipe->right->content->pipe->right->content->pipe->left->content->cmd->args[0]);