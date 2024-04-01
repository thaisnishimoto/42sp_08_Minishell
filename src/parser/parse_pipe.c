/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:33:31 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/01 17:29:01 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*parse_pipe(t_node *left, t_node *right)
{
	t_pipe	*pipe_node;

	pipe_node = ft_calloc(1, sizeof(t_pipe));
	pipe_node->type = PIPE;
	pipe_node->left = left;
	pipe_node->right = right;
	return ((t_node *)pipe_node);
}
