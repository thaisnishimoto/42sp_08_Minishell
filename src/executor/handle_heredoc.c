/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:10:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/10 22:55:27 by tmina-ni         ###   ########.fr       */
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
		update_exit_code(EXIT_FAILURE);
		return (0);
	}
	buffer = expand_hdoc(prompt("> "), node);
	while (ft_strncmp(buffer, node->eof, ft_strlen(node->eof) + 1) != 0)
	{
//		if (!input)
//			ft_putchar_fd('\n', 1);
		ft_putendl_fd(buffer, heredoc_fd);
		free(buffer);
		buffer = expand_hdoc(prompt("> "), node);
	}
	free(buffer);
	close(heredoc_fd);
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
				if (!get_heredoc_content(redir))
					return (0);
			}
			redir=redir->next;
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
