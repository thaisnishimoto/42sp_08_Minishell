/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:11:21 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/26 19:29:49 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	hashtable_free(t_env *hashtable[])
{
	int		i;
	t_env	*temp;

	i = 0;
	while (i < TABLE_SIZE)
	{
		while (hashtable[i])
		{
			temp = hashtable[i]->next;
			free(hashtable[i]->name);
			free(hashtable[i]->value);
			free(hashtable[i]);
			hashtable[i] = temp;
		}
		i++;
	}
}

void	print_hashtable(t_env *hashtable[])
{
	int		i;
	t_env	*temp;

	printf("\nSTART OF TABLE\n");
	i = 0;
	while (i < TABLE_SIZE)
	{
		if (hashtable[i])
		{
			temp = hashtable[i];
			while (temp)
			{
				printf("%d: %s=%s <-> ", i, temp->name, temp->value);
				temp = temp->next;
			}
			printf("\n");
		}
		else
			printf("%d: --empty--\n", i);
		i++;
	}
	printf("END OF TABLE\n");
}
