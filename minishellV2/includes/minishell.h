/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:20:26 by memahote          #+#    #+#             */
/*   Updated: 2024/02/18 17:13:59 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// -------------------------------- INCLUDES -----------------------------------

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

// -------------------------------- DEFINES ------------------------------------

# define FALSE			0
# define TRUE			1

# define NO				0
# define YES			1

# define ERROR_FOUND	1
# define EXIT_NO_CMD	2
# define GO_NEXT		3

# define E_QUOTES	"syntax error: unclosed quotes"
# define E_SYNTAX	"syntax error near unexpected token"
# define E_CMD		"command not found"
# define E_FILE		"no such file or directory"
# define E_DIR		"is a directory"
# define E_MALLOC	"malloc error"
# define E_PIPE		"pipe error"
# define E_DUP2		"dup2 error"
# define E_FORK		"fork error"
# define E_HEREDOC	"warning: here-document at line 1 delimited by end-of-file"
# define E_HOME		"HOME not set"
# define E_ARGS		"too many arguments"
# define E_NUM		"numeric argument required"
# define E_EXPORT	"not a valid identifier"

// ---------------------------- GLOBAL VARIABLES -------------------------------

extern int	g_exit_status;

// -------------------------------- STRUCTS ------------------------------------
typedef enum e_type
{
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR2_IN,
	T_REDIR2_OUT,
	T_OTHER,
	T_COMMAND,
	T_FILE_IN,
	T_FILE_TR,
	T_HEREDOC,
	T_FILE_AP,
	T_EMPTY,
}	t_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*content;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			**f_redin;
	char			**f_redout;
	int				*t_redin;
	int				*t_redout;
	int				has_heredoc;
	int				fd_in;
	int				fd_out;
	int				index;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minishell
{
	char			*input;
	char			**envp;
	char			**paths;
	int				**pipe_fd;
	int				n_pipes;
	pid_t			pid_heredoc;
	pid_t			*pid;
	int				file_error;
	int				heredoc_signal;
	int				heredoc_status;
	t_env			*env_lst;
	t_token			*token_lst;
	t_cmd			*cmd_lst;
}	t_minishell;

// main.c
void	ft_main_loop(t_minishell *ms);
void	ft_special_handler(char *input);
void	ft_free_all(t_minishell *ms, int free_pipes, int exit_flag);

// PARSING _____________________________________________________________________

int		ft_parser(t_minishell *ms, char *input);
int		ft_quote_checker(char *input);
void	ft_quote_remover(t_minishell *ms);
char	*ft_remove_quotes(char *cmd, int new_len, int i);
void	ft_tokenizer(t_minishell *ms, char *input);
int		ft_add_token(t_token **token_lst, char *input, t_type type);
int		ft_add_command_token(t_token **token_lst, char *input, t_type type);
int		ft_syntax_checker(t_minishell *ms, t_token *token);
t_token	*ft_new_token(char *input, t_type type);
void	ft_add_token_back(t_token **token, t_token *new_token);
void	ft_expander(t_minishell *ms, t_token *token);
void	ft_expand_command(t_minishell *ms, t_token *token);
char	*ft_get_key(char *cmd);
char	*ft_get_env_value(t_env **env_lst, char *key);
char	*ft_replace_content(char *cmd, char *key, char *value);
int		ft_last_check(t_minishell *ms);
int		ft_check_arg(t_minishell *ms);
int		ft_check_redir(t_minishell *ms, t_token *first, int n_args);
t_cmd	*ft_new_cmd(t_token *first, int n_args);
char	**ft_get_args(t_token *first, int n_args);
char	**ft_add_files(t_token *first, t_type type1, t_type type2);
int		*ft_add_types(t_token *first, t_type type1, t_type type2);
void	ft_add_cmd_back(t_cmd **cmd_table, t_cmd *new_cmd);

// ENVIRONMENT _________________________________________________________________

void	ft_init_env_lst(t_env **env, char **envp);
t_env	*ft_new_env(char *key, char *value);
void	ft_add_env_back(t_env **env_lst, t_env *new_env);
char	**ft_get_paths(t_env *env_lst);

// EXECUTION ___________________________________________________________________

void	ft_executer(t_minishell *ms);
void	ft_execute_only_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
int		ft_execute_mult_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
void	ft_execute_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
void	ft_execute_external(t_minishell *ms, t_cmd *curr, char *cmd);
int		ft_cmd_has_redir(t_cmd *cmd);
void	ft_handle_redir(t_minishell *ms, t_cmd *curr);
int		ft_open_fd(t_minishell *m, t_cmd *c, char *filename, t_type filetype);
void	ft_close_fds(t_cmd *curr);
int		ft_perror_fd(t_cmd *c, char *filename, t_type filetype);
int		ft_handle_heredoc(t_minishell *ms, char *delimiter);
void	ft_create_heredoc(t_minishell *ms, char *delimiter);
char	*ft_expand_heredoc(t_minishell *ms, char *line);
int		ft_count_pipes(t_cmd *cmd_lst);
void	ft_open_pipes(t_minishell *ms);
void	ft_handle_pipes(t_minishell *ms, t_cmd *curr);
void	ft_close_pipes(t_minishell *ms);

// BUILTINS ____________________________________________________________________

void	ft_cd(t_minishell *ms, t_cmd *curr);
int		ft_cd_arg(t_minishell *ms, t_cmd *curr, int arg_flag);
void	ft_echo(t_minishell *ms, t_cmd *curr);
int		ft_get_start_index(char **args);
void	ft_print_argument(char *s);
void	ft_env(t_minishell *ms, t_cmd *cur);
void	ft_exit(t_minishell *ms, t_cmd *curr);
int		ft_isnum(char *s);
void	ft_export(t_minishell *ms, t_cmd *curr);
int		ft_export_variable(t_minishell *ms, t_cmd *curr, int i);
void	ft_export_list(t_minishell *ms, t_cmd *curr);
void	ft_sort_env(t_env *env);
void	ft_swap_env(t_env *curr, t_env *next);
void	ft_pwd(t_minishell *ms, t_cmd *curr);
void	ft_unset(t_minishell *ms, t_cmd *curr);
void	ft_export_unset(t_minishell *ms, char *arg);
void	ft_unset_key(t_minishell *m, t_cmd *c, t_env *e, t_env *p);

// UTILS _______________________________________________________________________

int		ft_perror(t_minishell *ms, char *error, int free_flag, char *file);
int		ft_everything_is_space(char *str);
int		ft_count_redir(t_token *first, t_type type1, t_type type2);
void	ft_has_heredoc(t_minishell *ms);
int		ft_is_space(char c);
int		ft_is_symbol(char c);
int		ft_count_quotes(char *s);
int		ft_in_squote(char *cmd, char *stop);
int		ft_in_dquote(char *cmd, char *stop);
int		ft_is_forkable(t_minishell *ms, int execution_flag);
void	ft_set_cmd_index(t_minishell *ms);
void	ft_waitpid_handler(t_minishell *ms, int i, pid_t pid, int exec_flag);
char	*ft_find_path(char *cmd, char *possible_paths);
void	ft_execute_mult_cmd_helper(t_minishell *ms, t_cmd *curr, int flag);
void	ft_free_token_lst(t_token **token_lst);
void	ft_free_cmd_lst(t_cmd **cmd_table);
void	ft_free_env_lst(t_env **env_lst);
void	ft_free_str_array(char **str_array);
void	ft_free_pipes(t_minishell *ms);
bool	ft_cmd_has_valid_option(char **args);
void	ft_builtin_error(t_minishell *ms, t_cmd *curr, char *err, int ex_code);
char	*ft_find_env(t_env *env_lst, char *find);
void	ft_update_env(t_env **env_lst, char *key, char *update);
bool	ft_args_are_valid(char *arg, int export_flag);
void	ft_if_no_path(t_minishell *ms, t_cmd *curr, char *cmd);
void	ft_build_envp(t_minishell *ms);

// SIGNALS _____________________________________________________________________

void	ft_signals(void);
void	ft_signals_heredoc(void);
void	ft_signals_child(t_minishell *ms);
void	ft_free_heredoc(int signum, t_minishell *ms);
void	ft_handler_sigint(int signum);
void	ft_handler_heredoc(int signum);
void	ft_handler_child(int signum);

#endif
