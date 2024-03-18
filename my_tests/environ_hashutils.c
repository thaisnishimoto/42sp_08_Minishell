/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_hashutils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/15 17:56:03 by tmina-ni         ###   ########.fr       */
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
	else
		exit (43); // syntax error: quote not closed
	return (len);
}

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
}

void	hashtable_insert(t_env *hashtable[], t_env *new_var)
{
	int	index;

	index = hash_function(new_var->name);
	if (hashtable[index] == NULL)
		hashtable[index] = new_var;
	else
	{
		new_var->next = hashtable[index];
		hashtable[index] = new_var;
	}
}

void	hashtable_insert_replace(t_env *hashtable[], t_env *new_var)
{
	if (hashtable_search(hashtable, new_var->name))
		hashtable_delete(hashtable, new_var->name);
	hashtable_insert(hashtable, new_var);
}

void	init_hashtable(t_env *hashtable[])
{
	int	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		hashtable[i] = NULL;
		i++;
	}
}
