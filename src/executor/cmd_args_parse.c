/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:15:00 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/19 19:48:31 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*trim_quotes_arg(char *cmd_arg)
{
	char	**token_substr;
	int		i;

	if (cmd_arg == NULL)
		return (NULL);
	if (cmd_arg[0] == '\0')
		return (cmd_arg);
	token_substr = ft_split_concat_token(cmd_arg);
	if (token_substr == NULL)
		return (NULL);
	i = 0;
	while (token_substr[i])
	{
		token_substr[i] = ft_trim_quotes(token_substr[i], "\"\'");
		if (token_substr[i] == NULL)
		{
			ft_free_matrix(token_substr);
			return (NULL);
		}
		i++;
	}
	return (ft_rejoin_substr(token_substr));
}

static void	split_arg(t_list **parsed_args, char *cmd_arg)
{
	char	**token_mtx;
	int		i;
	t_list	*new_arg;

	token_mtx = ft_split(cmd_arg, ' ');
	if (token_mtx == NULL)
		return ;
	i = 0;
	while (token_mtx[i])
	{
		new_arg = ft_lstnew(ft_strdup(token_mtx[i]));
		if (new_arg == NULL)
		{
			ft_free_matrix(token_mtx);
			return ;
		}
		ft_lstadd_back(parsed_args, new_arg);
		i++;
	}
	ft_free_matrix(token_mtx);
}

void	cmd_args_parse(t_list **cmd_args)
{
	t_list	*parsed_args;
	t_list	*temp;
	char	*trimmed_arg;
	t_list	*new_arg;

	if (cmd_args == NULL)
		return ;
	parsed_args = NULL;
	temp = *cmd_args;
	while (temp)
	{
		if (ft_strchr(temp->content, '\"') || ft_strchr(temp->content, '\''))
		{
			trimmed_arg = trim_quotes_arg(ft_strdup(temp->content));
			new_arg = ft_lstnew(trimmed_arg);
			if (new_arg == NULL)
				break ;
			ft_lstadd_back(&parsed_args, new_arg);
		}
		else
			split_arg(&parsed_args, temp->content);
		temp = temp->next;
	}
	ft_lstclear(cmd_args, free);
	*cmd_args = parsed_args;
}
