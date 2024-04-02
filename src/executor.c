/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:10:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/01 23:20:11 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	executor(t_node *node)
{
	if (node == NULL)
		return ;
//	printf("\n");
//	if (node->type == PIPE)
//	{
//		t_pipe	*pipe_node = (t_pipe *)node;
//		printf("->node type: PIPE(%d)\n", pipe_node->type);
//		printf("\n---LEFT OF PIPE---");
//		print_tree((t_node *)pipe_node->left);
//		printf("\n---RIGHT OF PIPE---");
//		print_tree((t_node *)pipe_node->right);
//	}
//	else if (node->type == REDIR)
//	{
//		t_redir	*redir_node = (t_redir *)node;
//		printf("->node type: REDIR(%d)\n", redir_node->type);
//		printf("fd redir: %d\n", redir_node->fd);
//		printf("redir file: %s\n", redir_node->filename);
//		print_tree((t_node *)redir_node->next);
//	}
//	else if (node->type == HEREDOC)
//	{
//		t_redir	*redir_node = (t_redir *)node;
//		printf("->node type: HEREDOC(%d)\n", redir_node->type);
//		printf("redir delim: %s\n", redir_node->eof);
//		print_tree((t_node *)redir_node->next);
//	}
	if (node->type == CMD)
	{
		t_cmd	*cmd_node;
		pid_t	pid;
		int	wstatus;
		char	*msg;
		
		cmd_node = (t_cmd *)node;
		//check for builtin
		pid = fork();
//		if (pid < 0)
//			ft_handle_error();
		if (pid == 0)
			exec_cmd(cmd_node->cmd_args);
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
//		printf("exit code: %d\n", get_exit_code());
//		print_tree((t_node *)cmd_node->redirs);
	}
}
