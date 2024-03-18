/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_environ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:14:57 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/18 14:49:08 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_trim_quotes(char *str, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	trim_len;
	char	*ptr;

	if (str == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(str);
	if (ft_strchr(set, str[start]) && start < end)
		start++;
	if (ft_strrchr(set, str[end - 1]) && end > start)
		end--;
	trim_len = end - start;
	ptr = malloc((trim_len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, &str[start], trim_len + 1);
	free(str);
	return (ptr);
}

size_t	substr_env_name(char *str)
{
	size_t	len;

	len = 0;
	while (ft_isalpha(str[len]) || str[len] == '_')
		len++;
	return (len);
}

size_t	ft_substrlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
	{
		if (str[len] == '\'' || str[len] == '\"')
		{
			len += substr_quote(&str[len]);
			break ;
		}
		else if (str[len++] == '$')
		{
			len += substr_env_name(&str[len]);
			break ;
		}
		else
		{
			while (str[len] && !ft_strchr("\'\"$", str[len]))
				len++;
			break ;
		}
	}
	return (len);
}

int	count_token_substr(char *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i])
	{
		i += ft_substrlen(&token[i]);
		count++;
	}
	return (count);
}


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
		printf("token substr[%d] = %s\n", j, token_substr[j]);
		i += ft_substrlen(&token[i]);
		j++;
	}
	free(token);
	token = NULL;
	return (token_substr);
}

char	*ft_add_single_quote(char *token_substr)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin("\'", token_substr);
	free(token_substr);
	result = ft_strjoin(temp, "\'");
	free(temp);
	return (result);
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
		free(token_substr[i]);
		result = temp;
	}
	free(token_substr);
	return (result);
}

//char	*ft_getenv(char *name)
//{
//	t_env	**hashtable;
//	t_env	*result;
//	char	*env_value;
//
//	hashtable = static_environ_htable(NULL, NULL, READ);
//	env_value = ft_strdup("");
//	result = hashtable_search(hashtable, name);
//	if (result)
//		env_value = ft_strdup(result->value);
//	return (env_value);
//}

char	*expand_token(char *token)
{
	t_env	**hashtable;
	t_env	*result;
	char	*env_value;

	hashtable = static_environ_htable(NULL, NULL, READ);
	env_value = ft_strdup("");
	result = hashtable_search(hashtable, &token[1]);
	if (result)
		env_value = ft_strdup(result->value);
	free(token);
	return (env_value);
}

char	*parse_token(char *token, int nested)
{
	char	**token_substr;
	int		i;

	token_substr = ft_split_concat_token(token);
	i = -1;
	//printf("initiate expand\n");
	while (token_substr[++i])
	{
		if (token_substr[i][0] == '\"')
		{
			token_substr[i] = ft_trim_quotes(token_substr[i], "\"");
			token_substr[i] = parse_token(token_substr[i], 1);
		}
		else if (token_substr[i][0] == '\'')
		{
			token_substr[i] = ft_trim_quotes(token_substr[i], "\'");
			if (nested)
			{	
				token_substr[i] = parse_token(token_substr[i], 1);
				token_substr[i] = ft_add_single_quote(token_substr[i]);
			}
		}
		else if (token_substr[i][0] == '$')
			token_substr[i] = expand_token(token_substr[i]);
	}
	return (ft_rejoin_token_substr(token_substr));
}
