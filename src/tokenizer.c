/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:55:36 by mchamma           #+#    #+#             */
/*   Updated: 2024/03/08 16:07:43 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	substr_quote(char *str)
{
	size_t	len;
	char	quote;

	len = 0;
	quote = str[len++];
	while (str[len] != '\0' && str[len] != quote)
		len++;
	if (str[len] == quote)
		len++;
	else
		exit (43); // syntax error: quote not closed
	return (len);
}

size_t	substr_operator(char *str, int slen)
{
	size_t	len;

	len = 0;
	if (slen != 0)
		return (0);
	len++;
	while (str[len] && str[len] == str[len - 1])
		len++;
	return (len);
}

int	ft_token_len(char *str, char delim)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != delim)
	{
		if (str[len] == '\'' || str[len] == '\"')
			len += substr_quote(&str[len]);
		else if (ft_strchr("<|>", str[len]))
		{
			len += substr_operator(&str[len], len);
			break ;
		}
		else
			len++;
	}
	return (len);
}

int	ft_count_tokens(char *str, char delim)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == delim)
			i++;
		if (str[i] != '\0')
			count++;
		i += ft_token_len(&str[i], delim);
	}
	return (count);
}

char	**ft_strtok(char *input, char delim)
{
	char	**tokens;
	int		count;
	int		i;
	int		j;

	count = ft_count_tokens(input, delim);
	tokens = ft_calloc((count + 1), sizeof(char *));
	if (tokens == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count)
	{
		while (input[i] == delim)
			i++;
		tokens[j] = ft_calloc(ft_token_len(&input[i], delim) + 1, sizeof(char));
		if (tokens[j] == NULL)
			return (NULL);
		ft_strlcpy(tokens[j], &input[i], ft_token_len(&input[i], delim) + 1);
		i += ft_token_len(&input[i], delim);
		j++;
	}
	free(input);
	return (tokens);
}
