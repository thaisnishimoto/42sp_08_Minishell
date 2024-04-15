/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:10:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/15 11:25:09 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	exec_simple_cmd(t_node *node)
{
	t_cmd	*cmd_node;
	pid_t	pid;

	cmd_node = (t_cmd *)node;
	pid = ft_fork();
	if (pid < 0)
		return ;
	set_signals_exec_mode(pid);
	if (pid == 0)
	{
		if (exec_redir(cmd_node->redirs))
			exec_cmd((t_list *)cmd_node->cmd_args);
		ft_exit_child_process(last_exit_code(-1));
	}
	wait_for_cmd_process(pid, cmd_node->cmd_args);
}

static void	exec_pipeline(t_node *node)
{
	int	*pipe_fd_holder;

	pipe_fd_holder = malloc(2 * sizeof(int));
	if (pipe_fd_holder == NULL)
	{
		perror("pipe malloc failed");
		last_exit_code(EXIT_FAILURE);
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
	free(pipe_fd_holder);
}

static void	exec_builtin_in_parent(t_cmd *cmd_node)
{
	int	backup[2];
	int	is_exit;

	backup[0] = dup(STDIN_FILENO);
	backup[1] = dup(STDOUT_FILENO);
	is_exit = 0;
	if (exec_redir(cmd_node->redirs))
		is_exit = exec_builtin(cmd_node);
	if (dup2(backup[0], STDIN_FILENO) == -1)
	{
		perror("dup2 error");
		last_exit_code(EXIT_FAILURE);
		return ;
	}
	if (dup2(backup[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 error");
		last_exit_code(EXIT_FAILURE);
		return ;
	}
	close(backup[0]);
	close(backup[1]);
	if (is_exit)
		ft_free_exit();
}

void	executor(t_node *node)
{
	t_cmd	*cmd_node;

	cmd_node = (t_cmd *)node;
	if (node == NULL)
		return ;
	if (!handle_heredocs(node))
		return ;
	last_exit_code(0);
	if (node->type == CMD && ((t_cmd *)node)->cmd_args)
	{
		if (is_builtin((t_cmd *)node))
			exec_builtin_in_parent((t_cmd *)node);
		else
			exec_simple_cmd(node);
	}
	else if (node->type == PIPE)
		exec_pipeline(node);
}
