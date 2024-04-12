/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:10:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/12 17:57:47 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*create_tmp_filename(void)
{
	char		*filename;
	char		*file_id;
	static int	num;

	num++;
	file_id = ft_itoa(num);
	filename = ft_strjoin("/tmp/hdoc", file_id);
	free(file_id);
	return (filename);
}

static int	get_heredoc_content(t_redir *node)
{
	int		heredoc_fd;
	char	*buffer;

	node->filename = create_tmp_filename();
	heredoc_fd = open(node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (heredoc_fd < 0)
	{
		perror(node->filename);
		last_exit_code(EXIT_FAILURE);
		return (0);
	}
	buffer = expand_hdoc(prompt("> "), node);
	if (!buffer)
		handle_hdoc_ctrl_d(node->eof);
	while (buffer && ft_strcmp(buffer, node->eof) != 0)
	{
		ft_putendl_fd(buffer, heredoc_fd);
		free(buffer);
		buffer = expand_hdoc(prompt("> "), node);
		if (!buffer)
			handle_hdoc_ctrl_d(node->eof);
	}
	free(buffer);
	close(heredoc_fd);
	return (1);
}

static int	fork_heredoc(t_redir *node)
{
	pid_t	pid;
	int		wstatus;

	pid = ft_fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		set_hdoc_signal(pid);
		if (!get_heredoc_content(node))
			last_exit_code(EXIT_FAILURE);
		exit (last_exit_code(-1));
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		last_exit_code(WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
		last_exit_code(WTERMSIG(wstatus));
	return (1);
}

int	handle_heredoc(t_node *node)
{
	t_redir	*redir;

	if (node->type == CMD)
	{
		redir = ((t_cmd *)node)->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				if (!fork_heredoc(redir))
					return (0);
			}
			redir = redir->next;
		}
	}
	else
	{
		if (!handle_heredoc(((t_pipe *)node)->left))
			return (0);
		if (!handle_heredoc(((t_pipe *)node)->right))
			return (0);
	}
	return (1);
}
