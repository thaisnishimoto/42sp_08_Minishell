/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:45:50 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/26 19:29:30 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//void	ft_handle_error(char *error_msg, t_data *pipex, t_fd *fd, int stage)
void	ft_handle_error(char *error_msg)
{
//	ft_free_pipex(pipex, fd, stage);
	static_environ_htable(NULL, NULL, FREE);
	perror(error_msg);
	exit(EXIT_FAILURE);
}

void	free_matrix(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	update_exit_code(char *new_value)
{
	t_env	*new_var;

	new_var = create_environ("?", new_value);
	static_environ_htable(new_var, NULL, ADD);
}

int	get_exit_code(void)
{
	char	*env_value;
	int	exit_code;

	env_value = ft_getenv("?");
	exit_code = ft_atoi(env_value);
	free(env_value);
	return (exit_code);
}

//void	free_matrix_size(char **array, int size)
//{
//	int	i;
//
//	i = 0;
//	while (i < size)
//	{
//		free(array[i]);
//		i++;
//	}
//	free(array);
//	array = NULL;
//}
//
////void	ft_close_pipes(int **pipe, int count)
//{
//	int	i;
//
//	i = 0;
//	while (i < count)
//	{
//		close(pipe[i][0]);
//		close(pipe[i][1]);
//		free(pipe[i]);
//		i++;
//	}
//	free(pipe);
//}
//
//void	ft_free_pipex(t_data *pipex, t_fd *fd, int stage)
//{
//	int	i;
//
//	i = 0;
//	if (stage >= 1)
//	{
//		ft_free_matrix(pipex->path, pipex->path_count);
//		if (stage >= 2)
//		{
//			while (i < pipex->cmd_count)
//			{
//				ft_free_matrix(pipex->cmd_args[i], pipex->args_count[i]);
//				i++;
//			}
//			free(pipex->cmd_args);
//			free(pipex->args_count);
//		}
//		if (stage >= 3)
//			ft_close_pipes(fd->pipe, pipex->pipe_count);
//		if (stage == 4)
//			free(pipex->pid);
//	}
//}
//
//void	ft_handle_error(char *error_msg, t_data *pipex, t_fd *fd, int stage)
//{
//	ft_free_pipex(pipex, fd, stage);
//	perror(error_msg);
//	exit(EXIT_FAILURE);
//}
//
//void	wait_finish_pipe(t_fd *fd, t_data *pipex)
//{
//	int	i;
//
//	i = 0;
//	ft_close_pipes(fd->pipe, pipex->pipe_count);
//	while (i < pipex->cmd_count)
//	{
//		if (waitpid(pipex->pid[i], &pipex->wstatus, 0) == -1)
//			ft_handle_error("waitpid error", pipex, fd, 1);
//		if (WIFEXITED(pipex->wstatus))
//			pipex->exit_code = WEXITSTATUS(pipex->wstatus);
//		else if (WIFSIGNALED(pipex->wstatus))
//			pipex->exit_code = WTERMSIG(pipex->wstatus);
//		if (pipex->exit_code == 127)
//			ft_printf("%s: command not found\n", pipex->cmd_args[i][0]);
//		if (pipex->exit_code == 126)
//			ft_printf("%s: permission denied\n", pipex->cmd_args[i][0]);
//		i++;
//	}
//	ft_free_pipex(pipex, fd, 2);
//	free(pipex->pid);
//	close(STDIN_FILENO);
//	close(STDOUT_FILENO);
//	close(STDERR_FILENO);
//}
