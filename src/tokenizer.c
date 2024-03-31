/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:55:36 by mchamma           #+#    #+#             */
/*   Updated: 2024/03/31 10:53:20 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	validate_quotes(char *input)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			single_quote++;
		else if (input[i] == '\"')
			double_quote++;
		i++;
	}
	if (single_quote % 2 || double_quote % 2)
	{
		ft_putendl_fd("syntax error: quote not closed", 2);
		update_exit_code("2");
		return (0);
	}
	return (1);
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
	}
	free(input);
	return (tokens);
}
