/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:14:57 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/08 16:10:28 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	size_t	buf_substrlen(char *buffer)
{
	size_t	len;

	len = 0;
	if (buffer[len] == '$')
	{
		len++;
		len += substr_env_name(&buffer[len]);
		return (len);
	}
	else
	{
		while (buffer[len] && buffer[len] != '$')
			len++;
		return (len);
	}
}

static	int	count_buffer_substr(char *buffer)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (buffer[i])
	{
		i += buf_substrlen(&buffer[i]);
		count++;
	}
	return (count);
}

static char	**ft_split_hdoc(char *buffer)
{
	char	**buff_substr;
	int		count;
	int		i;
	int		j;

	count = count_buffer_substr(buffer);
	buff_substr = ft_calloc(count + 1, sizeof(char *));
	if (buff_substr == NULL)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < count)
	{
		buff_substr[j] = ft_calloc(buf_substrlen(&buffer[i]) + 1, sizeof(char));
		if (buff_substr[j] == NULL)
		{
			free_matrix(buff_substr);
			return (NULL);
		}
		ft_strlcpy(buff_substr[j], &buffer[i], buf_substrlen(&buffer[i]) + 1);
		i += buf_substrlen(&buffer[i]);
	}
	free(buffer);
	buffer = NULL;
	return (buff_substr);
}

char	*expand_hdoc(char *buffer, t_redir *node)
{
	char	**hdoc_substr;
	int		i;

	if (buffer == NULL)
		return (NULL);
	if (!node->eof_expand || !ft_strchr(buffer, '$'))
		return (buffer);
	hdoc_substr = ft_split_hdoc(buffer);
	if (hdoc_substr == NULL)
		return (NULL);
	i = 0;
	while (hdoc_substr[i])
	{
		if (hdoc_substr[i][0] == '$' && hdoc_substr[i][1] != '\0')
		{
			hdoc_substr[i] = expand_env(hdoc_substr[i]);
			if (hdoc_substr[i] == NULL)
			{
				free_matrix(hdoc_substr);
				return (NULL);
			}
		}
		i++;
	}
	return (ft_rejoin_substr(hdoc_substr));
}
