/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:10:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/13 23:12:57 by tmina-ni         ###   ########.fr       */
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

void	executor(t_node *node)
{
	t_cmd	*cmd_node;

	cmd_node = (t_cmd *)node;
	if (node == NULL)
		return ;
	if (!handle_heredocs(node))
		return ;
	if (node->type == CMD)
	{
		//check for builtin
		//exec_redir in parent
		//exec buiiltin
		//reset fds to stdin and stdout
		if (!ft_strcmp("cd", cmd_node->cmd_args->content))
			cd_call(cmd_node);
		else if (!ft_strcmp("echo", cmd_node->cmd_args->content))
			echo_call(cmd_node);
		else if (!ft_strcmp("env", cmd_node->cmd_args->content))
			env_call(cmd_node);
		else if (!ft_strcmp("exit", cmd_node->cmd_args->content))
			printf("exit_code = %i\n", exit_call(cmd_node));
		else if (!ft_strcmp("export", cmd_node->cmd_args->content))
			export_call(cmd_node);
		else if (!ft_strcmp("pwd", cmd_node->cmd_args->content))
			pwd_call();
		else if (!ft_strcmp("unset", cmd_node->cmd_args->content))
			unset_call(cmd_node);
		else
			exec_simple_cmd(node);
	}
	else if (node->type == PIPE)
		exec_pipeline(node);
}
