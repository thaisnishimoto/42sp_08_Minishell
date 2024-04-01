/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/01 17:26:02 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_getenv(char *name)
{
	t_env	**hashtable;
	t_env	*env;
	char	*env_value;

	env_value = NULL;
	hashtable = static_environ_htable(NULL, NULL, READ);
	env = hashtable_search(hashtable, name);
	if (env)
		env_value = ft_strdup(env->value);
	return (env_value);
}

t_env	*create_environ(char *name, char *value)
{
	t_env	*new_var;

	new_var = ft_calloc(1, sizeof(t_env));
	if (new_var == NULL)
		return (NULL);
	new_var->name = ft_strdup(name);
	if (new_var->name == NULL)
	{
		free(new_var);
		return (NULL);
	}
	if (value)
	{
		new_var->value = ft_strdup(value);
		if (new_var->value == NULL)
		{
			free(new_var);
			free(new_var->name);
			return (NULL);
		}
	}
	return (new_var);
}

void	update_exit_code(char *new_value)
{
	t_env	*new_var;

	new_var = create_environ("?", new_value);
	static_environ_htable(new_var, NULL, ADD);
}

int	get_exit_code(void)
{
	char	*env_value;
	int		exit_code;

	env_value = ft_getenv("?");
	exit_code = ft_atoi(env_value);
	free(env_value);
	return (exit_code);
}
