/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:10:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/10 20:53:11 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executor(t_node *node)
{
	if (node == NULL)
		return ;
	if (!handle_heredoc(node))
		return ;
//	update_exit_code(0);
	if (node->type == CMD)
	{
		t_cmd	*cmd_node;
		pid_t	pid;
		
		cmd_node = (t_cmd *)node;
		//check for builtin
		//exec_redir in parent
		//exec buiiltin
		//reset fds to stdin and stdout
		pid = ft_fork();
		if (pid < 0)
			return ;
		if (pid == 0)
		{
			if (exec_redir(cmd_node->redirs))
				exec_cmd((t_list *)cmd_node->cmd_args);
			ft_exit_child_process(get_exit_code());
		}
		//wait_for_cmd_process(pid, cmd_node->cmd_args->content);
		wait_for_cmd_process(pid, cmd_node->cmd_args);
	}
	else if (node->type == PIPE)
		exec_pipeline(node);
}
