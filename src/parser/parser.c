/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/11 15:50:38 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd	*init_cmd_node(t_cmd **cmd_node)
{
	*cmd_node = ft_calloc(1, sizeof(t_cmd));
	if (*cmd_node == NULL)
		return (NULL);
	(*cmd_node)->type = CMD;
	(*cmd_node)->redirs = NULL;
	(*cmd_node)->cmd_args = NULL;
	return (*cmd_node);
}

static t_node	*build_tree(char *tokens[])
{
	int		i;
	t_cmd	*cmd_node;

	i = 0;
	if (!init_cmd_node(&cmd_node))
		return (NULL);
	while (tokens[i])
	{
		if (!ft_strchr("<|>", tokens[i][0]))
		{
			if (!parse_cmd(&cmd_node, tokens, &i))
				break ;
		}
		else if (tokens[i][0] == '<' || tokens[i][0] == '>')
		{
			if (!parse_redir(&cmd_node->redirs, tokens, &i))
			{
				free_ast((t_node *)cmd_node);
				break ;
			}
		}
		else if (tokens[i][0] == '|')
			return (parse_pipe((t_node *)cmd_node, build_tree(&tokens[++i])));
	}
	return ((t_node *)cmd_node);
}

t_node	*parser(char *tokens[])
{
	t_node	*tree_ptr;

	if (tokens == NULL)
		return (NULL);
	tree_ptr = NULL;
	tree_ptr = build_tree(tokens);
	if (tree_ptr == NULL)
	{
		ft_putendl_fd("AST build failed", 2);
		last_exit_code(EXIT_FAILURE);
	}
	ft_free_matrix(tokens);
	return (tree_ptr);
}
