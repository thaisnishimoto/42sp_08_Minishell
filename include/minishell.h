/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:49:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/13 02:58:05 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h> //pipe, dup, access, execve, fork
# include <stdlib.h> //malloc, exit
# include <fcntl.h> //open
# include <sys/types.h> //pid_t
# include <sys/wait.h> //wait
# include <errno.h> //perror
# include "../libft/libft.h"

# define OPERATORS "<|>"
# define CMD 1
# define PIPE 2
# define REDIR 3
# define HEREDOC 4

# define INIT 0
# define DEL 1
# define ADD 2
# define READ 3
# define FREE 4
# define PRINT 5

# define TABLE_SIZE 97

extern int	g_signum;

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*sign;
	struct s_env	*next;
}	t_env;

typedef struct s_node
{
	int	type;
}	t_node;

typedef struct s_redir
{
	int				type;
	int				mode;
	int				fd;
	char			*filename;
	char			*eof;
	int				eof_expand;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	int		type;
	t_list	*cmd_args;
	t_redir	*redirs;
}	t_cmd;

typedef struct s_pipe
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_pipe;

//minishell loop functions
char			*prompt(char *symbol);
char			**tokenizer(char *input);
t_node			*parser(char *tokens[]);

//signals
void			set_signals_interactive_mode(void);
void			sigint_display_new_prompt(int signum);
void			set_signals_exec_mode(pid_t pid);
void			set_signals_hdoc(pid_t pid);
void			handle_hdoc_ctrl_d(char *expected_eof);
void			signal_received(char *buffer, char *expected_eof, int hdoc_fd);

//environ hashtable functions
void			hashtable_load(char **envp);
t_env			**hashtable_mx(t_env *new, char *key, int mode);
void			hashtable_init(t_env *hash[]);
void			hashtable_delete(t_env *hash[], char *key);
void			hashtable_insert_replace(t_env *hash[], t_env *new);
void			hashtable_print(t_env *hash[]);
void			hashtable_free_hash(t_env *hash[]);
void			hashtable_free_node(t_env *list);
void			hashtable_free_content(t_env *env);
t_env			*hashtable_create_node_type1(char *env);
t_env			*hashtable_create_node_type2(char *key, char *value);
t_env			*hashtable_search(char *key);
int				hashtable_count_content(void);
char			**hashtable_key_mtx(void);

//builtin
void			env_call(t_cmd *cmd_node);

//tokenizer and syntax utils
int				validate_quotes(char *input);
int				validate_syntax(char **tokens);
size_t			substr_quote(char *str);
size_t			substr_operator(char *str, int slen);

//parse functions
int				parse_cmd(t_cmd **cmd_node, char *tokens[], int *i);
int				parse_redir(t_redir **redirs_ptr, char *tokens[], int *i);
t_node			*parse_pipe(t_node *left, t_node *right);
char			*parse_token(char *token, int nested);

//parse token - utils
int				count_token_substr(char *token);
size_t			substr_env_name(char *str);
size_t			ft_substrlen(char *str);
char			*ft_trim_quotes(char *str, const char *set);
char			*ft_add_single_quote(char *token_substr);
char			*expand_env(char *token);
char			*ft_rejoin_substr(char *token_substr[]);

//executor functions
void			executor(t_node *node);
int				handle_heredocs(t_node *node);
char			*expand_hdoc(char *buffer, t_redir *node);
void			exec_cmd(t_list *cmd_args);
void			first_cmd_pipeline(t_node *node, int *pipe_fd);
void			middle_cmd_pipeline(t_node *node, int *pipe_fd);
void			last_cmd_pipeline(t_node *node, int *pipe_fd);
int				exec_redir(t_redir *node);

//exec utils
pid_t			ft_fork(void);
int				ft_pipe(int *pipe_fd);
void			ft_close_pipe(int *pipe_fd);
void			ft_exit_child_process(int exit_code);
void			wait_for_cmd_process(pid_t pid, t_list *cmd_args);

//free and exit function
void			free_ast(t_node *node);
void			ft_handle_error(char *error_msg);
t_node			*static_ast_holder(t_node *ast, int mode);
int				last_exit_code(int new_value);

#endif
