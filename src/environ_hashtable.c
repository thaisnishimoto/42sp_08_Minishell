/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_hashtable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/12 11:05:08 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_matrix(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

t_env	*get_environ_data(char *envp)
{
	t_env	*new_var;
	char	**var_content;

	new_var = ft_calloc(1, sizeof(t_env));
	if (new_var == NULL)
		return (NULL);
	var_content = ft_split(envp, '=');
	if (var_content == NULL)
		return (NULL);
	new_var->name = ft_strdup(var_content[0]);
	if (var_content[1])
		new_var->value = ft_strdup(var_content[1]);
	free_matrix(var_content, 2);
	return (new_var);
}

void	load_environ_hashtable(t_env *hashtable[], char *envp[])
{
	int		i;
	t_env	*new_var;

	init_hashtable(hashtable);
	i = 0;
	while (envp[i])
	{
		new_var = get_environ_data(envp[i]);
		hashtable_insert(hashtable, new_var);
		i++;
	}
}
