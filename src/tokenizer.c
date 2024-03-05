/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:25:43 by mchamma           #+#    #+#             */
/*   Updated: 2024/03/05 16:19:56 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	preserve_quoted_substr(char *str)
{
	size_t	len;
	char	quote;

	len = 0;
	if (str[len] == '\'' || str[len] == '\"')
	{
		quote = str[len++];
		while (str[len] != '\0' && str[len] != quote)
			len++;
		if (str[len] == quote)
			len++;
		else
			return (-1);
	}
	return (len);
}

size_t	skip_operator(char *str)
{
	size_t	len;
	char	operator;

	len = 0;
	operator = str[len];
	while (str[len] != '\0' && str[len] == operator)
		len++;
	return (len);
}

int	ft_token_len(char *str, char delim)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != delim)
	{
		if (ft_strchr("<|>", str[len]))
		{
			len += skip_operator(&str[len]);
			break ;
		}
		len += preserve_quoted_substr(&str[len]);
		while (str[len] && str[len] != delim)
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
