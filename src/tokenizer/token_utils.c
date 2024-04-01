/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 21:45:32 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/31 21:45:43 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
