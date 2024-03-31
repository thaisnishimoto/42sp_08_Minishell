/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:47:07 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/29 17:38:03 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tree(t_node *node)
{
	if (node == NULL)
		return ;
	printf("\n");
	if (node->type == PIPE)
	{
		t_pipe	*pipe_node = (t_pipe *)node;
		printf("->node type: PIPE(%d)\n", pipe_node->type);
		printf("\n---LEFT OF PIPE---");
		print_tree((t_node *)pipe_node->left);
		printf("\n---RIGHT OF PIPE---");
		print_tree((t_node *)pipe_node->right);
	}
	else if (node->type == REDIR)
	{
		t_redir	*redir_node = (t_redir *)node;
		printf("->node type: REDIR(%d)\n", redir_node->type);
		printf("fd redir: %d\n", redir_node->fd);
		printf("redir file: %s\n", redir_node->filename);
		print_tree((t_node *)redir_node->next);
	}
	else if (node->type == HEREDOC)
	{
		t_redir	*redir_node = (t_redir *)node;
		printf("->node type: HEREDOC(%d)\n", redir_node->type);
		printf("redir delim: %s\n", redir_node->eof);
		printf("eof expand: %d\n", redir_node->eof_expand);
		print_tree((t_node *)redir_node->next);
	}
	else if (node->type == CMD)
	{
		t_cmd	*cmd_node = (t_cmd *)node;
		t_list	*temp = cmd_node->cmd_args;
		printf("->node type: CMD(%d)\n", cmd_node->type);
		int	i = 0;
		while (temp)
		{
			printf("cmd arg[%d]: %s\n", i, (char *)temp->content);
			temp = temp->next;
		}
		print_tree((t_node *)cmd_node->redirs);
	}
}

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
	if (node == NULL)
		return ;
	if (node->type == PIPE)
	{
		t_pipe	*pipe_node = (t_pipe *)node;
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
	else if (mode == READ)
		print_tree(static_ast);
	return (static_ast);
}
