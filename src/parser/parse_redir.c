/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:25:30 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/06 16:45:50 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_following_str(char *tokens[], int *i, int type)
{
	if (type == REDIR)
		tokens[*i] = parse_token(tokens[*i], 0);
	else
		tokens[*i] = ft_trim_quotes(tokens[*i], "\"\'");
	if (tokens[*i] == NULL)
	{
		return (NULL);
	}
	return (ft_strdup(tokens[*i]));
}

static void	ft_redir_addback(t_redir **redirs_ptr, t_redir *new_redir)
{
	t_redir	*temp;

	if (*redirs_ptr == NULL)
		*redirs_ptr = new_redir;
	else
	{
		temp = *redirs_ptr;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_redir;
	}
}

static void	set_redir_options(t_redir *new_redir, char *token)
{
	new_redir->type = REDIR;
	if (token[0] == '<')
	{
		new_redir->fd = 0;
		new_redir->mode = O_RDONLY;
		if (token[1] == '<')
		{
			new_redir->type = HEREDOC;
			new_redir->eof_expand = 1;
		}
	}
	else if (token[0] == '>')
	{
		new_redir->fd = 1;
		if (token[1] == '>')
			new_redir->mode = O_WRONLY | O_APPEND | O_CREAT;
		else
			new_redir->mode = O_WRONLY | O_TRUNC | O_CREAT;
	}
}

int	parse_redir(t_redir **redirs_ptr, char *tokens[], int *i)
{
	t_redir	*new_redir;

	new_redir = ft_calloc(1, sizeof(t_redir));
	if (new_redir == NULL)
		return (0);
	set_redir_options(new_redir, tokens[*i]);
	(*i)++;
	if (new_redir->type == REDIR)
	{
		new_redir->filename = get_following_str(tokens, i, REDIR);
		if (new_redir->filename == NULL)
			return (0);
	}
	else if (new_redir->type == HEREDOC)
	{
		if (ft_strchr("\"\'", tokens[*i][0]))
			new_redir->eof_expand = 0;
		new_redir->eof = get_following_str(tokens, i, HEREDOC);
		if (new_redir->eof == NULL)
			return (0);
	}
	ft_redir_addback(redirs_ptr, new_redir);
	(*i)++;
	return (1);
}
