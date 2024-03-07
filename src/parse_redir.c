/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:25:30 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/07 15:51:15 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_following_str(char *tokens[], int *i)
{
	int		len;
	char	*str;

	if (ft_strchr(OPERATORS, tokens[*i][0]))
	{
		printf("syntax error near unexpected token '%s'\n", tokens[*i]);
		//set exit code to 2
		return (NULL);
	}
	len = ft_strlen(tokens[*i]) + 1;
	str = ft_calloc(len, sizeof(char));
	if (str)
	{
		ft_strlcpy(str, tokens[*i], len);
		if (str[0] == '\'' || str[0] == '\"')
			str = ft_trim_quotes(str, "\'\"");
	}
	return (str);
}

char	*ft_trim_quotes(char *str, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	trim_len;
	char	*ptr;

	if (str == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(str);
	if (ft_strchr(set, str[start]) && start < end)
		start++;
	if (ft_strrchr(set, str[end - 1]) && end > start)
		end--;
	trim_len = end - start;
	ptr = malloc((trim_len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, &str[start], trim_len + 1);
	free(str);
	return (ptr);
}

void	ft_redir_addback(t_redir **redirs_ptr, t_redir *new_redir)
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

void	set_redir_options(t_redir *new_redir, char *token)
{
	new_redir->type = REDIR;
	if (token[0] == '<')
	{
		if (token[1] == '<')
			new_redir->type = HEREDOC;
		else
		{
			new_redir->fd = 0;
			new_redir->mode = O_RDONLY;
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

void	parse_redir(t_redir **redirs_ptr, char *tokens[], int *i)
{
	t_redir	*new_redir;

	new_redir = ft_calloc(1, sizeof(t_redir));
	if (new_redir == NULL)
		return ;
	set_redir_options(new_redir, tokens[*i]);
	(*i)++;
	if (new_redir->type == REDIR)
		new_redir->filename = get_following_str(tokens, i);
	else if (new_redir->type == HEREDOC)
		new_redir->eof = get_following_str(tokens, i);
	ft_redir_addback(redirs_ptr, new_redir);
	(*i)++;
}
