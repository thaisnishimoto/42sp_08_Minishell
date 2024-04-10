/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:45:50 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/10 14:17:17 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		update_exit_code(EXIT_FAILURE);
	}
	return (pid);
}

int	ft_pipe(int *pipe_fd)
{
	int	return_value;

	return_value = pipe(pipe_fd);
	if (return_value == -1)
	{
		perror("pipe error");
		free(pipe_fd);
		update_exit_code(EXIT_FAILURE);
	}
	return (return_value);
}

void	ft_close_pipe(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	free(pipe_fd);
}

void	ft_exit_child_process(int exit_code)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	rl_clear_history();
	static_environ_htable(NULL, NULL, FREE);
	static_ast_holder(NULL, FREE);
	exit(exit_code);
}

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
