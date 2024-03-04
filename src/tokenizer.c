/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:25:43 by mchamma           #+#    #+#             */
/*   Updated: 2024/03/04 11:05:45 by tmina-ni         ###   ########.fr       */
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
		i += preserve_quoted_substr(&str[i]);
		while (str[i] && str[i] != delim)
			i++;
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
		tokens[j] = &input[i];
		i += preserve_quoted_substr(&input[i]);
		while (input[i] && input[i] != delim)
			i++;
		if (input[i] == delim)
			input[i++] = '\0';
		j++;
	}
	return (tokens);
}
