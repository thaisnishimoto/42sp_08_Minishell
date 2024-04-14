/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:10:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/13 23:26:46 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*open_tmp_filename(int *hdoc_fd)
{
	static int	num;
	char		*filename;
	char		*file_id;

	num++;
	file_id = ft_itoa(num);
	filename = ft_strjoin("/tmp/hdoc", file_id);
	free(file_id);
	*hdoc_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (*hdoc_fd < 0)
	{
		perror(filename);
		free(filename);
		filename = NULL;
		last_exit_code(EXIT_FAILURE);
	}
	return (filename);
}

static void	get_heredoc_content(t_redir *node, int hdoc_fd)
{
	char	*buffer;

	buffer = expand_hdoc(prompt("> "), node);
	handle_if_signaled(buffer, node->eof, hdoc_fd);
	while (buffer && ft_strncmp(buffer, node->eof,
			ft_strlen(node->eof) + 1) != 0)
	{
		ft_putendl_fd(buffer, hdoc_fd);
		free(buffer);
		buffer = expand_hdoc(prompt("> "), node);
		handle_if_signaled(buffer, node->eof, hdoc_fd);
	}
	free(buffer);
	close(hdoc_fd);
}

static int	wait_for_hdoc_process(pid_t pid)
{
	int		wstatus;

	if (waitpid(pid, &wstatus, 0) == -1)
	{
		perror("waitpid error");
		last_exit_code(EXIT_FAILURE);
		return (0);
	}
	if (WIFEXITED(wstatus))
		last_exit_code(WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
		last_exit_code(128 + WTERMSIG(wstatus));
	if (last_exit_code(-1) >= 130)
		return (0);
	return (1);
}

static int	exec_heredoc(t_redir *node)
{
	int		heredoc_fd;
	pid_t	pid;

	node->filename = open_tmp_filename(&heredoc_fd);
	if (node->filename == NULL)
		return (0);
	pid = ft_fork();
	if (pid < 0)
		return (0);
	set_signals_hdoc(pid);
	if (pid == 0)
	{
		get_heredoc_content(node, heredoc_fd);
		ft_exit_child_process(last_exit_code(-1));
	}
	close(heredoc_fd);
	if (!wait_for_hdoc_process(pid))
		return (0);
	return (1);
}

int	handle_heredocs(t_node *node)
{
	t_redir	*redir;

	if (node->type == CMD)
	{
		redir = ((t_cmd *)node)->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				if (!exec_heredoc(redir))
					return (0);
			}
			redir = redir->next;
		}
	}
	else
	{
		if (!handle_heredocs(((t_pipe *)node)->left))
			return (0);
		if (!handle_heredocs(((t_pipe *)node)->right))
			return (0);
	}
	return (1);
}
