/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:10:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/09 14:30:14 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	executor(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == CMD)
	{
		t_cmd	*cmd_node;
		pid_t	pid;
		
		cmd_node = (t_cmd *)node;
		if (!handle_heredoc(cmd_node->redirs))
			return ;
		update_exit_code(0);
		//check for builtin
		//if (ft_strncmp("env", cmd_node->cmd_args->content, ft_strlen("env") + 1) == 0)
		//	printf("env found\n");
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
	else if (node->type == PIPE)
		exec_pipeline(node);
}
