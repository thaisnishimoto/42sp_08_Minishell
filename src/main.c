/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/04 14:51:07 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tree(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == REDIR)
	{
		t_redir	*redir_node = (t_redir *)node;
		printf("node type: %d\n", redir_node->type);
		printf("fd redir: %d\n", redir_node->fd);
		printf("redir file: %s\n", redir_node->filename);
		print_tree((t_node *)redir_node->next);
	}
	else if (node->type == HEREDOC)
	{
		t_redir	*redir_node = (t_redir *)node;
		printf("node type: %d\n", redir_node->type);
		printf("redir delim: %s\n", redir_node->eof);
		print_tree((t_node *)redir_node->next);
	}
	else if (node->type == CMD)
	{
		t_cmd	*cmd_node = (t_cmd *)node;
		printf("node type: %d\n", cmd_node->type);
		int	i = 0;
		while (cmd_node->cmd_args[i])
		{
			printf("cmd arg[%d]: %s\n", i, cmd_node->cmd_args[i]);
			i++;
		}
		print_tree((t_node *)cmd_node->redirs);
	}
}

t_node	*parser(char *tokens[])
{
	int	i;
	t_node	*tree_ptr;
	t_redir	*redirs_ptr;
	
	i = 0;
	redirs_ptr = NULL;
	tree_ptr = NULL;
	while (tokens[i])
	{
		if (!ft_strchr("<|>", tokens[i][0]))
			tree_ptr = parse_cmd(&redirs_ptr, tokens, &i);
		else if (tokens[i][0] == '<' || tokens[i][0] == '>')
			parse_redir(&redirs_ptr, tokens, &i);
	}
	if (!tree_ptr)
		tree_ptr = (t_node *)redirs_ptr;
	return (tree_ptr);
}

//int	main(int argc, char *argv[], char *envp[])
int	main(void)
{
	char	*input; 
	char	**tokens;
	t_node	*ast;

	tokens = NULL;
	ast = NULL; 
	while (1)
	{
		input = readline("$ ");
		if (input && *input)
		{
			add_history(input);
			tokens = ft_strtok(input, ' ');
			if (tokens == NULL)
			{
				free(input);
				return (1);
			}
			ast = parser(tokens);
			printf("parse done\n");
			print_tree(ast);
			free(input);
			input = NULL;
		}
	}
	return (0);
}
