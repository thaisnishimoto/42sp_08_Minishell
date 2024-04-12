/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:46:54 by mchamma           #+#    #+#             */
/*   Updated: 2024/04/12 13:07:28 by mchamma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	hashtable_free_content(t_env *env)
{
	if (env)
	{
		free(env->key);
		free(env->value);
		free(env->sign);
		free(env);
	}
}

void	hashtable_free_node(t_env *node)
{
	t_env	*current;
	t_env	*next;

	current = node;
	while (current)
	{
		next = current->next;
		hashtable_free_content(current);
		current = next;
	}
}

void	hashtable_free_hash(t_env *hash[])
{
	int	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (hash[i])
		{
			hashtable_free_node(hash[i]);
			hash[i] = NULL;
		}
		i++;
	}
}

void	hashtable_print(t_env *hash[])
{
	int		i;
	t_env	*temp;

	printf("\nSTART OF TABLE\n");
	i = 0;
	while (i < TABLE_SIZE)
	{
		if (hash[i])
		{
			temp = hash[i];
			while (temp)
			{
				printf("%d: %s%s%s <> ", i, temp->key, temp->sign, temp->value);
				temp = temp->next;
			}
			printf("\n");
		}
		else
			printf("%d: --empty--\n", i);
		i++;
	}
	printf("END OF TABLE\n\n");
}
