/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:14:57 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/25 17:17:43 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_split_concat_token(char *token)
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
	j = 0;
	while (j < count)
	{
		token_substr[j] = ft_calloc(ft_substrlen(&token[i]) + 1, sizeof(char));
		if (token_substr[j] == NULL)
			return (NULL);
		ft_strlcpy(token_substr[j], &token[i], ft_substrlen(&token[i]) + 1);
//		printf("token substr[%d] = %s\n", j, token_substr[j]);
		i += ft_substrlen(&token[i]);
		j++;
	}
	free(token);
	token = NULL;
	return (token_substr);
}

char	*process_quotes(char *token_substr, int nested)
{
	if (token_substr[0] == '\"')
	{
		token_substr = ft_trim_quotes(token_substr, "\"");
		token_substr = parse_token(token_substr, 1);
	}
	else if (token_substr[0] == '\'')
	{
		token_substr = ft_trim_quotes(token_substr, "\'");
		if (nested)
		{
			token_substr = parse_token(token_substr, 1);
			token_substr = ft_add_single_quote(token_substr);
		}
	}
	return (token_substr);
}

char	*expand_token(char *token)
{
	t_env	**hashtable;
	t_env	*result;
	char	*env_value;

	if (token[1] == '\'' || token[1] == '\"')
		env_value = ft_trim_quotes(ft_strdup(&token[1]), "\"\'");
	else
	{
		hashtable = static_environ_htable(NULL, NULL, READ);
		result = hashtable_search(hashtable, &token[1]);
		if (result)
			env_value = ft_strdup(result->value);
		else
			env_value = ft_strdup("");
	}
	free(token);
	return (env_value);
}

char	*ft_rejoin_token_substr(char *token_substr[])
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
	free_matrix(token_substr);
	return (result);
}

char	*parse_token(char *token, int nested)
{
	char	**token_substr;
	int		i;

	if (token[0] == '\0')
		return (token);
	token_substr = ft_split_concat_token(token);
	i = 0;
	while (token_substr[i])
	{
		if (ft_strchr("\"\'", token_substr[i][0]))
			token_substr[i] = process_quotes(token_substr[i], nested);
		else if (token_substr[i][0] == '$' && token_substr[i][1] != '\0')
			token_substr[i] = expand_token(token_substr[i]);
		i++;
	}
	return (ft_rejoin_token_substr(token_substr));
}
