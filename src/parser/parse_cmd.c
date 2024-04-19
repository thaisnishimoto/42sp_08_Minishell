/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:33:31 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/19 08:49:55 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parse_cmd(t_cmd **cmd_node, char *tokens[], int *i)
{
	t_list	*new_arg;
	tokens[*i] = parse_token(tokens[*i]);
	if (tokens[*i] == NULL)
		return (0);
	new_arg = ft_lstnew(ft_strdup(tokens[*i]));
	if (new_arg == NULL)
		return (0);
	ft_lstadd_back(&(*cmd_node)->cmd_args, new_arg);
	(*i)++;
	return (1);
}
