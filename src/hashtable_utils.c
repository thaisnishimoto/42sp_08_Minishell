/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:11:21 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/01 14:21:37 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

unsigned int	hash_function(char *name)
{
	int				len;
	int				i;
	unsigned int	hash_value;

	len = ft_strlen(name);
	i = 0;
	hash_value = 0;
	while (i < len)
	{
		hash_value += name[i];
		hash_value = (hash_value * name[i]) % TABLE_SIZE;
		i++;
	}
	return (hash_value);
}

void	hashtable_init(t_env *hashtable[])
{
	int	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		hashtable[i] = NULL;
		i++;
	}
}

t_env	*hashtable_search(t_env *hashtable[], char *name)
{
	int		index;
	t_env	*result;

	index = hash_function(name);
	result = hashtable[index];
	while (result && ft_strncmp(result->name, name, ft_strlen(name)) != 0)
		result = result->next;
	return (result);
}

void	hashtable_delete(t_env *hashtable[], char *name)
{
	int		index;
	t_env	*temp;
	t_env	*prev;

	if (!hashtable_search(hashtable, name))
		return ;
	index = hash_function(name);
	prev = NULL;
	temp = hashtable[index];
	while (temp && ft_strncmp(temp->name, name, ft_strlen(name)) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (prev == NULL)
		hashtable[index] = temp->next;
	else
		prev->next = temp->next;
	free(temp->name);
	free(temp->value);
	free(temp);
}

void	hashtable_insert_replace(t_env *hashtable[], t_env *new_var)
{
	int	index;

	if (hashtable_search(hashtable, new_var->name))
		hashtable_delete(hashtable, new_var->name);
	index = hash_function(new_var->name);
	if (hashtable[index] == NULL)
		hashtable[index] = new_var;
	else
	{
		new_var->next = hashtable[index];
		hashtable[index] = new_var;
	}
}
