/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:14:57 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/15 18:35:14 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	*expand_env(char *token)
{
	t_env	*result;
	char	*env_value;

	if (token[1] == '\'' || token[1] == '\"')
		env_value = ft_trim_quotes(ft_strdup(&token[1]), "\"\'");
	else if (token[1] == '?')
		env_value = ft_itoa(last_exit_code(-1));
	else if (ft_isdigit(token[1]))
		env_value = ft_strdup(&token[2]);
	else
	{
		result = hashtable_search(&token[1]);
		if (result)
			env_value = ft_strdup(result->value);
		else
			env_value = ft_strdup("");
	}
	free(token);
	return (env_value);
}

char	*process_til(char *token_substr)
{
	char	*home_env;
	char	*temp;

	home_env = expand_env(ft_strdup("$HOME"));
	if (token_substr[1] == '\0')
	{
		free(token_substr);
		token_substr = ft_strdup(home_env);
	}
	else if (token_substr[1] == '/')
	{
		temp = ft_strjoin(home_env, &token_substr[1]);
		free(token_substr);
		token_substr = temp;
	}
	free(home_env);
	return (token_substr);
}
