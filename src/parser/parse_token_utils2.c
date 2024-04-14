/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:14:57 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/14 14:57:04 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

size_t	ft_substrlen(char *str)
{
	size_t	len;

	len = 0;
	if (str[len] == '\'' || str[len] == '\"')
	{
		len += substr_quote(&str[len]);
		return (len);
	}
	else if (str[len] == '$')
	{
		len++;
		if (str[len] == '\'' || str[len] == '\"')
			len += substr_quote(&str[len]);
		else
			len += substr_env_name(&str[len]);
		return (len);
	}
	else
	{
		while (str[len] && !ft_strchr("\'\"$", str[len]))
			len++;
		return (len);
	}
}

size_t	substr_env_name(char *str)
{
	size_t	len;

	len = 0;
	while (ft_isalnum(str[len]) || str[len] == '_' || str[len] == '?')
		len++;
	return (len);
}

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
	if (ptr)
		ft_strlcpy(ptr, &str[start], trim_len + 1);
	free(str);
	return (ptr);
}

char	*ft_add_single_quote(char *token_substr)
{
	char	*result;
	char	*temp;

	if (token_substr == NULL)
		return (NULL);
	temp = ft_strjoin("\'", token_substr);
	free(token_substr);
	result = ft_strjoin(temp, "\'");
	free(temp);
	return (result);
}
