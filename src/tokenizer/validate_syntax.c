/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:03:43 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/19 18:09:12 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	validate_quotes(char *input)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (!quote)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		i++;
	}
	if (quote)
	{
		ft_putendl_fd("syntax error: unclosed quotes", 2);
		last_exit_code(2);
		return (0);
	}
	return (1);
}

static int	check_pipe_syntax(char *prev_token, char *next_token)
{
	if ((prev_token == NULL) || (next_token == NULL))
	{
		ft_putendl_fd("syntax error near unexpected token '|'", 2);
		return (0);
	}
	return (1);
}

static int	check_redir_syntax(char *next_token)
{
	if (next_token == NULL)
	{
		ft_putendl_fd("syntax error near unexpected token 'newline'", 2);
		return (0);
	}
	else if (ft_strchr(OPERATORS, next_token[0]))
	{
		ft_putstr_fd("syntax error near unexpected token '", 2);
		ft_putstr_fd(next_token, 2);
		ft_putendl_fd("'", 2);
		return (0);
	}
	return (1);
}

int	validate_syntax(char **tokens)
{
	int		i;
	char	*prev_token;

	i = 0;
	prev_token = NULL;
	while (tokens[i])
	{
		if (tokens[i][0] == '|')
		{
			if (!check_pipe_syntax(prev_token, tokens[i + 1]))
				return (0);
		}
		else if (tokens[i][0] == '<' || tokens[i][0] == '>')
		{
			if (!check_redir_syntax(tokens[i + 1]))
				return (0);
		}
		prev_token = tokens[i];
		i++;
	}
	return (1);
}
