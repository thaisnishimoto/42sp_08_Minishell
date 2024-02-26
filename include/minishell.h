/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:49:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/02/25 23:47:47 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

# define CMD 1
# define PIPE 2
# define REDIR 3

typedef struct	s_node
{
	int	type;
}	t_node;

typedef struct	s_cmd
{
	int	type;
	char	*pathname;
	char	**cmd_args;
}	t_cmd;

typedef struct	s_redir
{
	int	type;
	char	*filename;
	int	fd;
	t_node	*next_node;
}	t_redir;

#endif
