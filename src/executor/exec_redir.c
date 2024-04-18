/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:10:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/18 00:54:24 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	expand_filename(t_redir *node)
{
	int		expand_flag;
	char	*redir_arg;

	redir_arg = ft_strdup(node->filename);
	if (redir_arg == NULL)
		return (0);
	expand_flag = 0;
	node->filename = parse_token(node->filename, &expand_flag);
	if (expand_flag && ft_strchr(node->filename, ' '))
	{
		last_exit_code(EXIT_FAILURE);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir_arg, 2);
		ft_putendl_fd(": ambiguous redirect", 2);
		free(redir_arg);
		return (0);
	}
	return (1);
}

static int	handle_infile_redir(t_redir *node)
{
	int	fd;

	fd = open(node->filename, node->mode);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(node->filename);
		last_exit_code(EXIT_FAILURE);
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 error");
		last_exit_code(EXIT_FAILURE);
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static int	handle_outfile_redir(t_redir *node)
{
	int	fd;

	fd = open(node->filename, node->mode, 0777);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(node->filename);
		last_exit_code(EXIT_FAILURE);
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 error");
		last_exit_code(EXIT_FAILURE);
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	exec_redir(t_redir *node)
{
	if (node == NULL)
		return (1);
	if (!expand_filename(node))
		return (0);
	if (node->fd == 0)
	{
		if (!handle_infile_redir(node))
			return (0);
	}
	else
	{
		if (!handle_outfile_redir(node))
			return (0);
	}
	if (!exec_redir(node->next))
		return (0);
	return (1);
}
