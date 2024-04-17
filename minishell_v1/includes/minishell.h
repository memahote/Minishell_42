/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:15:09 by memahote          #+#    #+#             */
/*   Updated: 2023/11/29 17:15:09 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "lexer.h"
#include <sys/wait.h>
# include "limits.h"


struct s_tree_node;
struct s_list_env;

typedef	struct s_list_env
{
	char	*name;
	char	*value;
	struct s_list_env *prev;
	struct s_list_env *next;
}	t_list_env;

typedef struct s_env
{
	t_list_env *head;
	char		**envp;
	int			len;
}	t_env;


enum e_tree_type
{
    CMD,
    PIPE,
};

typedef struct s_list_redir
{
    char *file;
    enum e_token type;
    struct s_list_redir *next;
}   t_list_redir;

typedef struct s_cmd
{
    char    **args;
	int		nb_args;
    char    **env;
    t_list_redir *redir;
    int fd_in;
    int fd_out;
}   t_cmd;

typedef struct s_pipe
{
    struct s_tree_node *left;
    struct s_tree_node *right;
}   t_pipe;

typedef union u_type
{
    t_pipe  *pipe;
    t_cmd   *cmd;
}   t_type;

typedef struct s_tree_node
{
    enum e_tree_type type;
    t_type  *content;
}   t_tree_node;

typedef struct s_tree
{
    t_tree_node *tree_root;
}   t_tree;

typedef struct s_data
{
	int		exit_status;
	int		pid;
	t_env	*env;
	t_list	*token_list;
	t_tree	*tree;
	char	**envp;
}		t_data;

//			######------ PARSER ------######

int	parser(t_tree **tree, t_list *token, char **env);
char	*parse_quotes(char *args, t_list **token);
int	count_args(t_list *token);
char	*get_env(char *env);
t_tree_node	*new_cmd(char **args, t_list_redir *redir, char **env, int len);
t_tree_node	*parse_pipe(t_list **token);
t_list_redir	*new_redir_cont(char *file, enum e_token type);
void	add_back_redir(t_list_redir **lst, t_list_redir *new);
char	*get_env(char *env);
t_tree	*init_tree(t_tree *tree);
int	check_quote_input(char *line);
void	free_tree(t_tree_node *node);
void	free_cmd(t_cmd *cmd);
void	fill_redirl(t_list_redir **redir_l, t_list **token);

//			######### PRINT ##########
void print_arg(char	**args);
void	print_tree_node(t_tree_node *cmd);
void	print_tree(t_tree_node *tree);
void print_redir(t_list_redir *redirl);

int	ft_pwd(void);


//			######## BUILTINS #######
t_env	*create_env(char **envp);
void	add_back_env(t_env *env, t_list_env *new);
t_list_env	*new_var_env(char *var);
int	ft_echo(t_cmd *cmd, int fd_out);
int	ft_strchr_env(char	*str, int c);
int	ft_export(t_env *env, t_cmd *cmd);
int	ft_unset(t_env *env, t_cmd *cmd);
int	ft_cd(t_cmd *cmd);
int	ft_env(t_env *env, t_cmd *cmd);
void	print_env_sort(t_list_env **env);
int	check_builtins(char	*arg);
void	which_builtins(t_cmd *cmd, t_env *env, int builtins);
void	print_sorted_env(t_env *env);
int execute_command(t_cmd *cmd, t_env *env, int p_fd[2]);
void execute_tree(t_tree_node *node, t_env *env);
char	*get_path(t_cmd *cmd, char **envp);
int	execute_cmd(t_cmd *cmd, char **env, int fd[2]);
void	check_fd_execve(t_cmd *cmd, int fd[2]);
t_env	*init_env(t_env	*env);
void	do_redir(t_list_redir *list, int *fd_in, int *fd_out);
int	ft_strchr_ex(char *s, int c);

//a supp
void print_env(t_list_env *env);
#endif