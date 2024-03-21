/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:33:31 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/20 15:37:32 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_cmd_arg(t_list **cmd_args, char *token)
{
	t_list	*new_arg;

	new_arg = ft_lstnew(token);
	if (new_arg == NULL)
		return ;
	ft_lstadd_back(cmd_args, new_arg);
}

void	parse_cmd(t_cmd **cmd_node, char *tokens[], int *i)
{
	if (*cmd_node == NULL)
	{
		*cmd_node = ft_calloc(1, sizeof(t_cmd));
		if (*cmd_node == NULL)
			return ;
		(*cmd_node)->type = CMD;
		(*cmd_node)->redirs = NULL;
		(*cmd_node)->cmd_args = NULL;
	}
	tokens[*i] = parse_token(tokens[*i], 0);
	add_cmd_arg(&((*cmd_node)->cmd_args), tokens[*i]);
	(*i)++;
}
