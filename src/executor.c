/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:10:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/09 12:10:57 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	wait_for_cmd_process(pid_t pid, char *cmd)
{
	int	wstatus;
	char	*msg;

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		update_exit_code(WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
		update_exit_code(WTERMSIG(wstatus));
	if (get_exit_code() == 126)
	{
		msg = ft_strjoin(cmd, ": Permission denied");
		ft_putendl_fd(msg, 2);
		free(msg);
	}
	else if (get_exit_code() == 127)
	{
		msg = ft_strjoin(cmd, ": command not found");
		ft_putendl_fd(msg, 2);
		free(msg);
	}
}

void	first_cmd_pipeline(t_node *node, int *pipe_fd)
{
	t_cmd	*cmd_node;
	pid_t	pid;

	cmd_node = (t_cmd *)node;
	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		update_exit_code(EXIT_FAILURE);
		return ;
	}
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		free(pipe_fd);
		exec_cmd((t_list *)cmd_node->cmd_args);
	}
	close(pipe_fd[1]);
	wait_for_cmd_process(pid, cmd_node->cmd_args->content);
}

void	last_cmd_pipeline(t_node *node, int *pipe_fd)
{
	t_cmd	*cmd_node;
	pid_t	pid;

	cmd_node = (t_cmd *)node;
	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		update_exit_code(EXIT_FAILURE);
		return ;
	}
	if (pid == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		free(pipe_fd);
		exec_cmd((t_list *)cmd_node->cmd_args);
	}
	close(pipe_fd[0]);
	wait_for_cmd_process(pid, cmd_node->cmd_args->content);
}

void	executor(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == PIPE)
	{
		t_pipe	*pipe_node;
		int	*pipe_fd;
		
		pipe_node = (t_pipe *)node;
		pipe_fd = malloc(2 * sizeof(int));
		if (pipe_fd == NULL)
		{
			perror("pipe malloc failed");
			update_exit_code(EXIT_FAILURE);
			return ;
		}
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe error");
			update_exit_code(EXIT_FAILURE);
			return ;
		}
		first_cmd_pipeline(pipe_node->left, pipe_fd);
		last_cmd_pipeline(pipe_node->right, pipe_fd);
	}
	if (node->type == CMD)
	{
		t_cmd	*cmd_node;
		pid_t	pid;
		
		cmd_node = (t_cmd *)node;
		if (!handle_heredoc(cmd_node->redirs))
			return ;
		update_exit_code(0);
		//check for builtin
		if (ft_strncmp("env", cmd_node->cmd_args->content, ft_strlen("env") + 1) == 0)
			printf("env found\n");
		pid = fork();
//		if (pid < 0)
//			ft_handle_error();
		if (pid == 0)
		{
			if (!exec_redir(cmd_node->redirs))
				return ;
			exec_cmd(cmd_node->cmd_args);
		}
		wait_for_cmd_process(pid, cmd_node->cmd_args->content);
	}
}
