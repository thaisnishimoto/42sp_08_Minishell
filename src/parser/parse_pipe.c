/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:33:31 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/17 10:49:59 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*parse_pipe(t_node *left, t_node *right)
{
	t_pipe	*pipe_node;

	pipe_node = ft_calloc(1, sizeof(t_pipe));
	if (pipe_node == NULL)
	{
		free_ast(left);
		free_ast(right);
		return (NULL);
	}
	pipe_node->type = PIPE;
	pipe_node->left = left;
	pipe_node->right = right;
	if (pipe_node->right == NULL)
	{
		free_ast(left);
		return (NULL);
	}
	return ((t_node *)pipe_node);
}
