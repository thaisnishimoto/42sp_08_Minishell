/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:10:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/20 12:10:30 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_redir_file_error(int exit_code, char *redir_arg)
{
	last_exit_code(exit_code);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(redir_arg, 2);
	ft_putendl_fd(": ambiguous redirect", 2);
}

static int	expand_filename(t_redir *node)
{
	char	*redir_arg;

	redir_arg = ft_strdup(node->filename);
	if (redir_arg == NULL)
		return (0);
	node->filename = parse_token(node->filename);
	if (node->filename[0] == '\0')
	{
		print_redir_file_error(EXIT_FAILURE, redir_arg);
		free(redir_arg);
		return (0);
	}
	else if (ft_strchr("\"\'", node->filename[0]))
		node->filename = ft_trim_quotes(node->filename, "\"\'");
	else if (ft_strchr(node->filename, ' '))
	{
		print_redir_file_error(EXIT_FAILURE, redir_arg);
		free(redir_arg);
		return (0);
	}
	free(redir_arg);
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
