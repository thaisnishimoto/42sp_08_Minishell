/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:14:57 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/12 13:00:08 by mchamma          ###   ########.fr       */
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

static char	*process_quotes(char *token_substr, int nested)
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

char	*expand_env(char *token)
{
	// t_env	**hashtable;
	t_env	*result;
	char	*env_value;

	if (token[1] == '\'' || token[1] == '\"')
		env_value = ft_trim_quotes(ft_strdup(&token[1]), "\"\'");
	else if (token[1] == '?')
		env_value = ft_itoa(last_exit_code(-1));
	else
	{
		// hashtable = static_environ_htable(NULL, NULL, READ);
		// result = hashtable_search(hashtable, &token[1]);
		result = hashtable_search(&token[1]);
		if (result)
			env_value = ft_strdup(result->value);
		else
			env_value = ft_strdup("");
	}
	free(token);
	return (env_value);
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
	i = -1;
	while (token_substr[++i])
	{
		if (ft_strchr("\"\'", token_substr[i][0]))
			token_substr[i] = process_quotes(token_substr[i], nested);
		else if (token_substr[i][0] == '$' && token_substr[i][1] != '\0')
			token_substr[i] = expand_env(token_substr[i]);
		if (token_substr[i] == NULL)
		{
			ft_free_matrix(token_substr);
			return (NULL);
		}
	}
	return (ft_rejoin_substr(token_substr));
}
