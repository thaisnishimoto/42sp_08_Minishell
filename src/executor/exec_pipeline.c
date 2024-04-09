/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:00:52 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/09 15:54:27 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	first_cmd_pipeline(t_node *node, int *pipe_fd)
{
	t_cmd	*cmd_node;
	pid_t	pid;
	
	cmd_node = (t_cmd *)node;
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
		exec_cmd((t_list *)cmd_node->cmd_args);
	}
	close(pipe_fd[1]);
	wait_for_cmd_process(pid, cmd_node->cmd_args->content);
}

static void	middle_cmd_pipeline(t_node *node, int *pipe_fd)
{
	int	prev_pipe_fd;
	t_cmd	*cmd_node;
	pid_t	pid;
	
	prev_pipe_fd = pipe_fd[0]; 
	cmd_node = (t_cmd *)node;
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
		dup2(prev_pipe_fd, STDIN_FILENO);
		close(prev_pipe_fd);
		dup2(pipe_fd[1], STDOUT_FILENO);
		ft_close_pipe(pipe_fd);
		exec_cmd((t_list *)cmd_node->cmd_args);
	}
	close(prev_pipe_fd);
	close(pipe_fd[1]);
	wait_for_cmd_process(pid, cmd_node->cmd_args->content);
}

static void	last_cmd_pipeline(t_node *node, int *pipe_fd)
{
	t_cmd	*cmd_node;
	pid_t	pid;
	
	cmd_node = (t_cmd *)node;
	pid = ft_fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		ft_close_pipe(pipe_fd);
		exec_cmd((t_list *)cmd_node->cmd_args);
	}
	close(pipe_fd[0]);
	free(pipe_fd);
	wait_for_cmd_process(pid, cmd_node->cmd_args->content);
}

void	exec_pipeline(t_node *node)
{
	int	*pipe_fd_holder;

	pipe_fd_holder = malloc(2 * sizeof(int));
	if (pipe_fd_holder == NULL)
	{
		perror("pipe malloc failed");
		update_exit_code(EXIT_FAILURE);
		return ;
	}
	first_cmd_pipeline(((t_pipe *)node)->left, pipe_fd_holder);
	node = ((t_pipe *)node)->right;
	while (node->type == PIPE)
	{
		middle_cmd_pipeline(((t_pipe *)node)->left, pipe_fd_holder);
		node = ((t_pipe *)node)->right;
	}
	last_cmd_pipeline(node, pipe_fd_holder);
}
