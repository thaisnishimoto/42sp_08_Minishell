/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:49:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/04 14:00:51 by tmina-ni         ###   ########.fr       */
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

# define CMD 1
# define PIPE 2
# define REDIR 3
# define HEREDOC 4

typedef struct	s_node
{
	int	type;
}	t_node;

typedef struct	s_redir
{
	int	type;
	int	mode;
	int	fd;
	char	*filename;
	char	*eof;
	struct s_redir	*next;
}	t_redir;

typedef struct	s_cmd
{
	int	type;
//	char	*pathname;
	char	**cmd_args;
	t_redir	*redirs;
}	t_cmd;

//tokenizer functions
char	**ft_strtok(char *input, char delim);
int	ft_count_tokens(char *str, char delim);
size_t	preserve_quoted_substr(char *str);
void	nulterminate_tok(char **tokens, char delim, int tok_count);

//parse redirection functions
void	parse_redir(t_redir **redirs_ptr, char *tokens[], int *i);
void	set_redir_options(t_redir *new_redir, char *token);
char	*get_following_str(char *tokens[], int *i);
char	*ft_trim_quotes(char *str, const char *set);
void	ft_redir_addback(t_redir **redirs_ptr, t_redir *new_redir);

//parse command function
t_node	*parse_cmd(t_redir **redirs_ptr, char *tokens[], int *i);

#endif
