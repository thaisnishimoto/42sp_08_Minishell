/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:14:57 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/19 09:43:01 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_str_insert(char *str, char *insert, int pos, int skip_len)
{
	char	*final_str;
	char	*aux_join;
	char	*str_start;
	char	*str_end;
	int		end_len;

	str_start = ft_calloc(pos + 1, sizeof(char));
	if (str_start == NULL)
		return (NULL);
	ft_strlcpy(str_start, str, pos + 1);
	aux_join = ft_strjoin(str_start, insert);
	free(str_start);
	if (aux_join == NULL)
		return (NULL);
	end_len = ft_strlen(&str[pos + skip_len]);
	str_end = ft_calloc(end_len + 1, sizeof(char));
	if (str_end == NULL)
		return (NULL);
	ft_strlcpy(str_end, &str[pos + skip_len], end_len + 1);
	final_str = ft_strjoin(aux_join, str_end);
	free(aux_join);
	free(str_end);
	free(str);
	free(insert);
	return (final_str);
}

char	*expand_quoted_str(char *str)
{
	int		i;
	int		env_len;
	char	*env_key;
	char	*env_value;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'
				|| str[i + 1] == '?'))
		{
			env_len = substr_env_name(&str[i + 1]) + 1;
			env_key = ft_substr(str, i, env_len);
			env_value = expand_env(env_key);
			str = ft_str_insert(str, env_value, i, env_len);
			if (str == NULL)
			{
				last_exit_code(EXIT_FAILURE);
				return (NULL);
			}
			i += env_len;
		}
		else
			i++;
	}
	return (str);
}

char	*expand_env(char *token)
{
	t_env	*result;
	char	*env_value;

	if (token[1] == '\"')
		env_value = expand_quoted_str(ft_strdup(&token[1]));
	else if (token[1] == '\'')
		env_value = ft_strdup(&token[1]);
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
