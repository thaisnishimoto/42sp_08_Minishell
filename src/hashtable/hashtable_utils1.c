/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 12:02:32 by mchamma           #+#    #+#             */
/*   Updated: 2024/04/12 13:09:09 by mchamma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

unsigned int	hashtable_index_convert(char *key)
{
	unsigned int	index;
	int				len;
	int				i;

	len = ft_strlen(key);
	index = 0;
	i = 0;
	while (i < len)
	{
		index += key[i];
		index = (index * key[i]) % TABLE_SIZE;
		i++;
	}
	return (index);
}

t_env	*hashtable_search(char *key)
{
	t_env	**hash;
	t_env	*current;
	int		index;

	hash = hashtable_mx(NULL, NULL, READ);
	index = hashtable_index_convert(key);
	current = hash[index];
	while (current)
	{
		if (!ft_strcmp(current->key, key))
			return (current);
		current = current->next;
	}
	return (current);
}

void	hashtable_delete(t_env *hash[], char *key)
{
	t_env	*current;
	t_env	*prev;
	int		index;

	index = hashtable_index_convert(key);
	prev = NULL;
	current = hash[index];
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			if (!prev)
				hash[index] = current->next;
			else
			prev->next = current->next;
			hashtable_free_content(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

void	hashtable_insert_replace(t_env *hash[], t_env *new)
{
	int		index;

	if (hashtable_search(new->key))
		hashtable_mx(NULL, new->key, DEL);
	index = hashtable_index_convert(new->key);
	if (!hash[index])
		hash[index] = new;
	else
	{
		new->next = hash[index];
		hash[index] = new;
	}
}

void	hashtable_init(t_env *hash[])
{
	int	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		hash[i] = NULL;
		i++;
	}
}
