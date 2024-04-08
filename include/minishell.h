/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:49:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/08 16:13:34 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
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

typedef struct s_env
{
	char			*name;
	char			*value;
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

//environ hashtable functions
t_env			**static_environ_htable(t_env *new_var, char *name, int mode);
void			load_environ_hashtable(char *envp[]);
char			*ft_getenv(char *name);
t_env			*create_environ(char *name, char *value);
void			update_exit_code(int new_value);
int				get_exit_code(void);

//hashtable utils functions
void			hashtable_init(t_env *hashtable[]);
t_env			*hashtable_search(t_env *hashtable[], char *name);
void			hashtable_delete(t_env *hashtable[], char *name);
void			hashtable_insert_replace(t_env *hashtable[], t_env *new_var);
void			hashtable_free(t_env *hashtable[]);
void			print_hashtable(t_env *hashtable[]);

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
void			exec_cmd(t_list *cmd_args);
int				exec_redir(t_redir *node);

//heredoc exec functions
int				handle_heredoc(t_redir *node);
char			*expand_hdoc(char *buffer, t_redir *node);

//free and exit function
void			free_ast(t_node *node);
void			free_matrix(char **array);
void			ft_handle_error(char *error_msg);
t_node			*static_ast_holder(t_node *ast, int mode);

#endif
