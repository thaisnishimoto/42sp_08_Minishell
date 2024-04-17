/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:45:50 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/17 17:15:27 by tmina-ni         ###   ########.fr       */
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
		last_exit_code(EXIT_FAILURE);
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
		last_exit_code(EXIT_FAILURE);
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
	hashtable_mx(NULL, NULL, FREE);
	static_ast_holder(NULL, FREE);
	exit(exit_code);
}

void	wait_for_cmd_process(pid_t pid)
{
	int		wstatus;

	if (waitpid(pid, &wstatus, 0) == -1)
	{
		perror("waitpid error");
		return ;
	}
	if (WIFEXITED(wstatus))
		last_exit_code(WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
		last_exit_code(128 + WTERMSIG(wstatus));
	else if (last_exit_code(-1) == 130)
		write(1, "\n", 1);
	else if (last_exit_code(-1) == 131)
		ft_putendl_fd("Quit (core dumped)", 2);
}
