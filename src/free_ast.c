/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:47:07 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/20 18:09:06 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_redir_node(t_redir *redir_node)
{
	t_redir	*temp;

	while (redir_node)
	{
		if (redir_node->filename)
			free(redir_node->filename);
		if (redir_node->eof)
			free(redir_node->eof);
		temp = redir_node;
		redir_node = redir_node->next;
		free(temp);
	}
}

void	free_cmd_node(t_cmd *cmd_node)
{
	t_list	*args;
	t_list	*temp;

	if (cmd_node->redirs)
		free_redir_node(cmd_node->redirs);
	args = cmd_node->cmd_args;
	while (args)
	{
		if (args->content)
			free(args->content);
		temp = args;
		args = args->next;
		free(temp);
	}
	free(cmd_node);
}

void	free_ast(t_node *node)
{
	t_pipe	*pipe_node;

	if (node == NULL)
		return ;
	if (node->type == PIPE)
	{
		pipe_node = (t_pipe *)node;
		free_ast((t_node *)pipe_node->left);
		free_ast((t_node *)pipe_node->right);
		free(pipe_node);
	}
	else if (node->type == CMD)
		free_cmd_node((t_cmd *)node);
	else if (node->type == REDIR || node->type == HEREDOC)
		free_redir_node((t_redir *)node);
}

t_node	*static_ast_holder(t_node *ast, int mode)
{
	static t_node	*static_ast;

	if (mode == INIT)
		static_ast = ast;
	else if (mode == FREE)
		free_ast(static_ast);
	else if (mode == PRINT)
		print_tree(static_ast);
	return (static_ast);
}
