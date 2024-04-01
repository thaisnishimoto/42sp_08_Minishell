/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:55:36 by mchamma           #+#    #+#             */
/*   Updated: 2024/03/31 22:32:13 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_token_len(char *str, char delim)
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

static int	ft_count_tokens(char *str, char delim)
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

static char	**ft_strtok(char *input, char delim)
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
	j = -1;
	while (++j < count)
	{
		while (input[i] == delim)
			i++;
		tokens[j] = ft_calloc(ft_token_len(&input[i], delim) + 1, sizeof(char));
		if (tokens[j] == NULL)
		{
			free_matrix(tokens);
			return (NULL);
		}
		ft_strlcpy(tokens[j], &input[i], ft_token_len(&input[i], delim) + 1);
		i += ft_token_len(&input[i], delim);
	}
	return (tokens);
}

char	**tokenizer(char *input)
{
	char	**tokens;

	if (input == NULL)
		return (NULL);
	tokens = NULL;
	if (validate_quotes(input))
	{
		tokens = ft_strtok(input, ' ');
		if (tokens == NULL)
		{
			ft_putendl_fd("tokenizer: malloc failed", 2);
			update_exit_code("1");
		}
		else if (!validate_syntax(tokens))
		{
			update_exit_code("2");
			free_matrix(tokens);
			tokens = NULL;
		}
	}
	free(input);
	input = NULL;
	return (tokens);
}
