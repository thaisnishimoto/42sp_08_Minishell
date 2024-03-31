/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:03:43 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/31 10:26:37 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	substr_quote(char *str)
{
	size_t	len;
	char	quote;

	len = 0;
	quote = str[len++];
	while (str[len] != '\0' && str[len] != quote)
		len++;
	if (str[len] == quote)
		len++;
	return (len);
}

size_t	substr_operator(char *str, int slen)
{
	size_t	len;

	len = 0;
	if (slen != 0)
		return (0);
	len++;
	while (str[len] && str[len] == str[len - 1])
		len++;
	return (len);
}

int	ft_token_len(char *str, char delim)
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

int	ft_count_tokens(char *str, char delim)
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

