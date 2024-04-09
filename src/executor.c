/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:10:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/09 00:17:18 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	executor(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == PIPE)
	{
		t_pipe	*pipe_node;
		int	pipe_fd[2];
		pid_t	pid;
	//	int	wstatus;
		
		pipe_node = (t_pipe *)node;
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe error");
			update_exit_code(EXIT_FAILURE);
			return ;
		}
		pid = fork();
//		if (pid < 0)
//			ft_handle_error();
		if (pid == 0)
		{
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			close(pipe_fd[0]);
			exec_cmd((t_list *)((t_cmd *)pipe_node->left)->cmd_args);
		}
		else
		{
			close(pipe_fd[1]);
	//		waitpid(pid, &wstatus, 0);
	//		if (WIFEXITED(wstatus))
	//			update_exit_code(WEXITSTATUS(wstatus));
	//		else if (WIFSIGNALED(wstatus))
	//			update_exit_code(WTERMSIG(wstatus));
		}
		pid = fork();
//		if (pid < 0)
//			ft_handle_error();
		if (pid == 0)
		{
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[1]);
			close(pipe_fd[0]);
			exec_cmd((t_list *)((t_cmd *)pipe_node->right)->cmd_args);
		}
		else
		{
			close(pipe_fd[0]);
	//		waitpid(pid, &wstatus, 0);
	//		if (WIFEXITED(wstatus))
	//			update_exit_code(WEXITSTATUS(wstatus));
	//		else if (WIFSIGNALED(wstatus))
	//			update_exit_code(WTERMSIG(wstatus));
		}
	}
	if (node->type == CMD)
	{
		t_cmd	*cmd_node;
		pid_t	pid;
		int	wstatus;
		char	*msg;
		
		cmd_node = (t_cmd *)node;
		if (!handle_heredoc(cmd_node->redirs))
			return ;
		update_exit_code(0);
		//check for builtin
		pid = fork();
//		if (pid < 0)
//			ft_handle_error();
		if (pid == 0)
		{
			if (!exec_redir(cmd_node->redirs))
				return ;
			exec_cmd(cmd_node->cmd_args);
		}
		else
		{
			waitpid(pid, &wstatus, 0);
			if (WIFEXITED(wstatus))
				update_exit_code(WEXITSTATUS(wstatus));
			else if (WIFSIGNALED(wstatus))
				update_exit_code(WTERMSIG(wstatus));
			if (get_exit_code() == 126)
			{
				msg = ft_strjoin(cmd_node->cmd_args->content, ": Permission denied");
				ft_putendl_fd(msg, 2);
				free(msg);
			}
			else if (get_exit_code() == 127)
			{
				msg = ft_strjoin(cmd_node->cmd_args->content, ": command not found");
				ft_putendl_fd(msg, 2);
				free(msg);
			}
		}
	}
}
