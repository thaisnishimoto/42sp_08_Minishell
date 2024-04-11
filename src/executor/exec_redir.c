/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:10:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/11 15:48:39 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
