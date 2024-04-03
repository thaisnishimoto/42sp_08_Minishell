/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:33:31 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/03 16:48:39 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parse_cmd(t_cmd **cmd_node, char *tokens[], int *i)
{
	t_list	*new_arg;

	tokens[*i] = parse_token(tokens[*i], 0);
	if (tokens[*i] == NULL)
	{
		free_ast((t_node *)*cmd_node);
		return (0);
	}
	new_arg = ft_lstnew(ft_strdup(tokens[*i]));
	if (new_arg == NULL)
	{
		free_ast((t_node *)*cmd_node);
		return (0);
	}
	ft_lstadd_back(&(*cmd_node)->cmd_args, new_arg);
	(*i)++;
	return (1);
}
