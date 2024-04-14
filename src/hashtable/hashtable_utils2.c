/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 11:59:16 by mchamma           #+#    #+#             */
/*   Updated: 2024/04/12 19:25:43 by mchamma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	hashtable_count_content(void)
{
	t_env	**hash;
	t_env	*temp;
	int		count;
	int		i;

	hash = hashtable_mx(NULL, NULL, READ);
	count = 0;
	i = 0;
	while (i < TABLE_SIZE)
	{
		temp = hash[i];
		while (temp)
		{
			count++;
			temp = temp->next;
		}
		i++;
	}
	return (count);
}

char	**hashtable_key_mtx(void)
{
	t_env	**hash;
	t_env	*temp;
	char	**key;
	int		i;
	int		j;

	hash = hashtable_mx(NULL, NULL, READ);
	key = ft_calloc(hashtable_count_content() + 1, sizeof(char *));
	j = 0;
	i = 0;
	while (i < TABLE_SIZE)
	{
		temp = hash[i];
		while (temp)
		{
			key[j++] = ft_strdup(temp->key);
			temp = temp->next;
		}
		i++;
	}
	return (key);
}

char	**hashtable_key_mtx_sorted(void)
{
	char	**key;
	char	*temp;
	int		i;
	int		j;

	key = hashtable_key_mtx();
	i = 0;
	while (key[i])
	{
		j = 0;
		while (key[j + 1])
		{
			if (ft_strcmp(key[j], key[j + 1]) > 0)
			{
				temp = key[j];
				key[j] = key[j + 1];
				key[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (key);
}
