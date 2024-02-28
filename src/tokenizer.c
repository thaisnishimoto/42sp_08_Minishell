/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/02/28 14:18:41 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	preserve_quoted_substr(char *str)
{
	size_t	len;

	len = 0;
	if (str[len] == '\'')
	{
		len++;
		while (str[len] != '\'')
			len++;
		len++;
	}
	else if (str[len] == '\"')
	{
		len++;
		while (str[len] != '\"')
			len++;
		len++;
	}
	return (len);
}

int	ft_count_tokens(char *str, char delim)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == delim)
			i++;
		if (str[i] != '\0')
			count++;
		if (str[i] == '\'' || str[i] == '\"')
			i += preserve_quoted_substr(&str[i]);
		while (str[i] && str[i] != delim)
			i++;
	}
	return (count);
}

void	nulterminate_tok(char **tokens, char delim, int tok_count)
{
	int	i;
	int	j;

	j = 0;
	while (j < tok_count)
	{
		i = 0;
		if (tokens[j][i] == '\'' || tokens[j][i] == '\"')
			i += preserve_quoted_substr(tokens[j]);
		while (tokens[j][i] != delim && tokens[j][i])
			i++;
		tokens[j][i] = '\0';
//		printf("token[%d]: %s\n", j, tokens[j]);
		j++;
	}
}

char	**ft_strtok(char *input, char delim)
{
	int		tok_count;
	int		i;
	int		j;
	char	**tokens;

	tok_count = ft_count_tokens(input, delim);
	i = 0;
	j = 0;
	tokens = malloc((tok_count + 1) * sizeof(char *));
	if (tokens == NULL)
		return (NULL);
	tokens[tok_count] = NULL;
	while (j < tok_count)
	{
		while (input[i] == delim)
			i++;
		tokens[j] = &input[i];
		j++;
		if (input[i] == '\'' || input[i] == '\"')
			i += preserve_quoted_substr(&input[i]);
		while (input[i] && input[i] != delim)
			i++;
	}
	nulterminate_tok(tokens, delim, tok_count);
	return (tokens);
}
