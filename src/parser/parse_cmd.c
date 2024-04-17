/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:33:31 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/17 20:36:58 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_list	*lst_args(t_list **cmd_args, char *token)
{
	char	**token_mtx;
	int		i;
	t_list	*new_arg;

	token_mtx = ft_split(token, ' ');
	if (token_mtx == NULL)
		return (NULL);
	i = 0;
	while (token_mtx[i])
	{
		new_arg = ft_lstnew(ft_strdup(token_mtx[i]));
		if (new_arg == NULL)
			return (NULL);
		ft_lstadd_back(cmd_args, new_arg);
		i++;
	}
	return (*cmd_args);
}

int	parse_cmd(t_cmd **cmd_node, char *tokens[], int *i, int export_flag)
{
	t_list	*new_arg;
	int	expand_flag;

//	(void)export_flag;
	expand_flag = 0;
	tokens[*i] = parse_token(tokens[*i], &expand_flag);
	if (tokens[*i] == NULL)
		return (0);
//	if (expand_flag == 1 && ft_strchr(tokens[*i], '='))
	if (expand_flag == 1 && !export_flag)
	{
		if (!lst_args(&(*cmd_node)->cmd_args, tokens[*i]))
			return (0);
	}
	else
	{
		new_arg = ft_lstnew(ft_strdup(tokens[*i]));
		if (new_arg == NULL)
			return (0);
		ft_lstadd_back(&(*cmd_node)->cmd_args, new_arg);
	}
	(*i)++;
	return (1);
}
