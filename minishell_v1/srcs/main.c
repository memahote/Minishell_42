/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 00:58:48 by memahote          #+#    #+#             */
/*   Updated: 2024/01/03 00:58:48 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/lexer.h"
#include "../includes/minishell.h"

void print_tokens(t_list *token);
void print_env(t_list_env *env) ;

void	init_data(t_data *data)
{
	data->exit_status = 0;
	data->pid = 0;
	data->env = NULL;
	data->tree = NULL;
	data->token_list = NULL;
}

void	start_minishell(t_data *data, char **envp)
{
	data->envp = envp;
	data->tree = init_tree(data->tree);
	data->env = create_env(envp);
}

int		ft_prompt(char **line)
{
	*line = readline("minishell~>"); 
	if (!*line)
	{
		printf("exit\n");
		exit(1);
	}
	if (strcmp(*line, "") == 0)
		return (1);
	if(ft_strlen(*line) > 0)
		add_history(*line);
	return (0);
}

void	minishell(t_data *data, char **envp)
{
	char	*line;
	t_env	*enves;

	line = NULL;
	enves = create_env(envp);
	while (42)
	{
		start_minishell(data, envp);
		if (ft_prompt(&line))
			continue ;
		if(!check_quote_input(line))
		{
				perror("Unclose quote");
				continue ;
		}
		data->token_list = lexer(line);
		if (!check_syntax(&data->token_list))
		{
			if (parser(&data->tree, data->token_list, data->envp) == EXIT_FAILURE)
				continue ;
			execute_tree(data->tree->tree_root, enves);
			// print_tokens(data->token_list);
			// print_tree(data->tree->tree_root);
		}
		else
		{
			free(data->token_list);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	if (argc !=1 || !*envp)
		return (1);
	init_data(&data);
	minishell(&data, envp);
}

void print_env(t_list_env *env) 
{
	while (env) 
	{
        printf("%s=%s\n", env->name, env->value);
        env = env->next;
    }
}

void print_tokens(t_list *tokens) 
{
	while (tokens) 
	{
        printf("Type1: %d, Content: %s, State: %d\n", tokens->type, tokens->content, tokens->state);
        tokens = tokens->next;
    }
}