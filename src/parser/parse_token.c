/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:14:57 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/17 00:20:31 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**ft_split_concat_token(char *token)
{
	char	**token_substr;
	int		count;
	int		i;
	int		j;

	count = count_token_substr(token);
	token_substr = ft_calloc(count + 1, sizeof(char *));
	if (token_substr == NULL)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < count)
	{
		token_substr[j] = ft_calloc(ft_substrlen(&token[i]) + 1, sizeof(char));
		if (token_substr[j] == NULL)
		{
			ft_free_matrix(token_substr);
			return (NULL);
		}
		ft_strlcpy(token_substr[j], &token[i], ft_substrlen(&token[i]) + 1);
		i += ft_substrlen(&token[i]);
	}
	free(token);
	token = NULL;
	return (token_substr);
}

static char	*process_substr(char *token_substr, int nested)
{
	(void)nested;
	if (ft_strchr("\"\'", token_substr[0]))
		token_substr = process_quotes(token_substr);
	else if (token_substr[0] == '$' && token_substr[1] != '\0')
		token_substr = expand_env(token_substr);
	else if (token_substr[0] == '~')
		token_substr = process_til(token_substr);
	return (token_substr);
}

char	*ft_rejoin_substr(char *token_substr[])
{
	char	*result;
	char	*temp;
	int		i;

	i = 0;
	result = ft_strdup(token_substr[i]);
	while (token_substr[++i])
	{
		temp = ft_strjoin(result, token_substr[i]);
		free(result);
		result = temp;
	}
	ft_free_matrix(token_substr);
	return (result);
}

char	*parse_token(char *token, int nested)
{
	char	**token_substr;
	int		i;

	if (token == NULL)
		return (NULL);
	if (token[0] == '\0')
		return (token);
	token_substr = ft_split_concat_token(token);
	if (token_substr == NULL)
		return (NULL);
	i = 0;
	while (token_substr[i])
	{
		token_substr[i] = process_substr(token_substr[i], nested);
		if (token_substr[i] == NULL)
		{
			ft_free_matrix(token_substr);
			return (NULL);
		}
		i++;
	}
	return (ft_rejoin_substr(token_substr));
}
