/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/01 18:00:05 by tmina-ni         ###   ########.fr       */
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
		printf("cmd pathname: %s\n", cmd_node->pathname);
		print_tree((t_node *)cmd_node->redirs);
	}
}

//t_node	*parse_cmd(t_node **tree_ptr, char *tokens[], int *i)
//{
//	t_cmd	*new_node;
//	char	*operators = "<|>";
//
//	node = malloc(sizeof(t_cmd));
//	new_root->filename = malloc(ft_strlen(&tokens[*i][j]) + 1 * sizeof(char));
//	ft_strlcpy(new_root->filename, &tokens[*i][j], ft_strlen(&tokens[*i][j]));
//	new_root->next_node = tree_ptr;
//}

t_node	*parser(char *tokens[])
{
	int	i;
//	t_node	*tree_ptr;
	t_redir	*redirs_ptr;
//	char	*operators = "<|>";

	i = 0;
	redirs_ptr = NULL;
//	tree_ptr = NULL;
	while (tokens[i])
	{
//		if (ft_strchr(operators, tokens[i][0]))
//			tree_ptr = parse_cmd(&redirs_ptr, tokens, &i);
		if (tokens[i][0] == '<' || tokens[i][0] == '>')
			parse_redir(&redirs_ptr, tokens, &i);
	}
	return ((t_node *)redirs_ptr);
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
			print_tree(ast);
			free(input);
			input = NULL;
		}
	}
	return (0);
}
