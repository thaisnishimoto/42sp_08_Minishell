/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:00:52 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/09 13:18:40 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	first_cmd_pipeline(t_cmd *node, int *pipe_fd)
{
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe error");
		free(pipe_fd);
		update_exit_code(EXIT_FAILURE);
		return ;
	}
	pid = ft_fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		ft_close_pipe(pipe_fd);
		exec_cmd((t_list *)node->cmd_args);
	}
	close(pipe_fd[1]);
	wait_for_cmd_process(pid, node->cmd_args->content);
}

static void	last_cmd_pipeline(t_cmd *node, int *pipe_fd)
{
	pid_t	pid;

	pid = ft_fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		ft_close_pipe(pipe_fd);
		exec_cmd((t_list *)node->cmd_args);
	}
	close(pipe_fd[0]);
	wait_for_cmd_process(pid, node->cmd_args->content);
}

void	exec_pipeline(t_pipe *node)
{
	int	*pipe_fd_holder;

	pipe_fd_holder = malloc(2 * sizeof(int));
	if (pipe_fd_holder == NULL)
	{
		perror("pipe malloc failed");
		update_exit_code(EXIT_FAILURE);
		return ;
	}
	first_cmd_pipeline((t_cmd *)node->left, pipe_fd_holder);
	last_cmd_pipeline((t_cmd *)node->right, pipe_fd_holder);
}
