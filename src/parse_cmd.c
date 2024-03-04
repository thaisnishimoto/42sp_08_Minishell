/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:33:31 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/04 14:49:04 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*parse_cmd(t_redir **redirs_ptr, char *tokens[], int *i)
{
	t_cmd	*cmd_node;
	int		count;
	int		j;

	cmd_node = malloc(sizeof(t_cmd));
	*cmd_node = (t_cmd){};
	cmd_node->type = CMD;
	count = 0;
	while (tokens[*i + count] && !ft_strchr("<|>", tokens[*i + count][0]))
		count++;
	cmd_node->cmd_args = ft_calloc((count + 1), sizeof(char *));
	if (cmd_node == NULL)
		return (NULL);
	j = 0;
	while (j < count)
	{
		cmd_node->cmd_args[j] = tokens[*i];
		j++;
		(*i)++;
	}
	cmd_node->redirs = *redirs_ptr;
	return ((t_node *)cmd_node);
}
