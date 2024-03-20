/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:49:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/20 12:00:21 by tmina-ni         ###   ########.fr       */
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

//hashtable utils functions
void			hashtable_init(t_env *hashtable[]);
void			hashtable_insert_replace(t_env *hashtable[], t_env *new_var);
void			hashtable_delete(t_env *hashtable[], char *name);
t_env			*hashtable_search(t_env *hashtable[], char *name);
void			hashtable_free(t_env *hashtable[]);
void			print_hashtable(t_env *hashtable[]);
unsigned int	hash_function(char *name);
t_env			**static_environ_htable(t_env *new_var, char *name, int mode);
void			load_environ_hashtable(char *envp[]);
char			*handle_quotes(char *token);

//tokenizer functions
char			**ft_strtok(char *input, char delim);
int				ft_count_tokens(char *str, char delim);
int				ft_token_len(char *str, char delim);
size_t			substr_quote(char *str);
size_t			substr_operator(char *str, int slen);
char			*parse_token(char *token, int nested);

//parse redirection functions
void			parse_redir(t_redir **redirs_ptr, char *tokens[], int *i);
void			set_redir_options(t_redir *new_redir, char *token);
char			*get_following_str(char *tokens[], int *i);
char			*ft_trim_quotes(char *str, const char *set);
void			ft_redir_addback(t_redir **redirs_ptr, t_redir *new_redir);

//parse command function
void			parse_cmd(t_cmd **cmd_node, char *tokens[], int *i);

//parse token functions
char			*parse_token(char *token, int nested);
char			**ft_split_concat_token(char *token);
char			*expand_token(char *token);
char			*ft_rejoin_token_substr(char *token_substr[]);
//parse token - utils
int				count_token_substr(char *token);
size_t			substr_env_name(char *str);
size_t			ft_substrlen(char *str);
char			*ft_trim_quotes(char *str, const char *set);
char			*ft_add_single_quote(char *token_substr);

//parse pipe function
t_node			*parse_pipe(t_node *left, t_node *right);

//free and exit function
void			free_matrix(char **array);
void			ft_handle_error(char *error_msg);

#endif
