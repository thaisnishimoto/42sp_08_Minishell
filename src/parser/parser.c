/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/02 14:32:48 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_node	*build_tree_branch(t_cmd *cmd_node, t_redir *redirs_ptr)
{
	if (!cmd_node)
		return ((t_node *)redirs_ptr);
	else
	{
		cmd_node->redirs = redirs_ptr;
		return ((t_node *)cmd_node);
	}
}

static t_node	*build_tree(char *tokens[])
{
	int		i;
	t_node	*tree_ptr;
	t_redir	*redirs_ptr;
	t_cmd	*cmd_node;

	i = 0;
	tree_ptr = NULL;
	redirs_ptr = NULL;
	cmd_node = NULL;
	while (tokens[i])
	{
		if (!ft_strchr("<|>", tokens[i][0]))
			parse_cmd(&cmd_node, tokens, &i);
		else if (tokens[i][0] == '<' || tokens[i][0] == '>')
			parse_redir(&redirs_ptr, tokens, &i);
		else if (tokens[i][0] == '|')
		{
			tree_ptr = build_tree_branch(cmd_node, redirs_ptr);
			tree_ptr = parse_pipe(tree_ptr, build_tree(&tokens[++i]));
			break ;
		}
	}
	if (!tree_ptr)
		tree_ptr = build_tree_branch(cmd_node, redirs_ptr);
	return (tree_ptr);
}

t_node	*parser(char *tokens[])
{
	t_node	*tree_ptr;

	if (tokens == NULL)
		return (NULL);
	tree_ptr = NULL;
	tree_ptr = build_tree(tokens);
	free_matrix(tokens);
	return (tree_ptr);
}
