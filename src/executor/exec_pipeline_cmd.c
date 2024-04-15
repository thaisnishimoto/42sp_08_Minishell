/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:00:52 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/15 15:11:57 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	run_pipeline_cmd(t_cmd *cmd_node)
{
	if (exec_redir(cmd_node->redirs))
	{
		if (is_builtin(cmd_node))
			exec_builtin(cmd_node);
		else
			exec_cmd((t_list *)cmd_node->cmd_args);
	}
	ft_exit_child_process(last_exit_code(-1));
}

void	first_cmd_pipeline(t_node *node, int *pipe_fd)
{
	t_cmd	*cmd_node;
	pid_t	pid;

	cmd_node = (t_cmd *)node;
	if (ft_pipe(pipe_fd) == -1)
		return ;
	pid = ft_fork();
	if (pid < 0)
		return ;
	set_signals_exec_mode(pid);
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		ft_close_pipe(pipe_fd);
		run_pipeline_cmd(cmd_node);
	}
	close(pipe_fd[1]);
}

void	middle_cmd_pipeline(t_node *node, int *pipe_fd)
{
	int		prev_pipe_fd;
	t_cmd	*cmd_node;
	pid_t	pid;

	prev_pipe_fd = pipe_fd[0];
	cmd_node = (t_cmd *)node;
	if (ft_pipe(pipe_fd) == -1)
		return ;
	pid = ft_fork();
	if (pid < 0)
		return ;
	set_signals_exec_mode(pid);
	if (pid == 0)
	{
		dup2(prev_pipe_fd, STDIN_FILENO);
		close(prev_pipe_fd);
		dup2(pipe_fd[1], STDOUT_FILENO);
		ft_close_pipe(pipe_fd);
		run_pipeline_cmd(cmd_node);
	}
	close(prev_pipe_fd);
	close(pipe_fd[1]);
}

void	last_cmd_pipeline(t_node *node, int *pipe_fd)
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
		dup2(pipe_fd[0], STDIN_FILENO);
		ft_close_pipe(pipe_fd);
		run_pipeline_cmd(cmd_node);
	}
	close(pipe_fd[0]);
}

int	wait_for_pipeline_cmds(void)
{
	pid_t	done_pid;
	static pid_t	last_cmd_pid;
	int		wstatus;

	done_pid = wait(&wstatus);
	if (done_pid > last_cmd_pid)
	{
		if (WIFEXITED(wstatus))
			last_exit_code(WEXITSTATUS(wstatus));
		else if (WIFSIGNALED(wstatus))
			last_exit_code(128 + WTERMSIG(wstatus));
	}
	last_cmd_pid = done_pid;
	return (done_pid);
}
