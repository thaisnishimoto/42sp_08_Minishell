/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:14:57 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/14 15:02:18 by tmina-ni         ###   ########.fr       */
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
