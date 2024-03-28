/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_hashtable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/26 11:29:14 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	**static_environ_htable(t_env *new_var, char *name, int mode)
{
	static t_env	*hashtable[TABLE_SIZE];

	if (mode == INIT)
		hashtable_init(hashtable);
	else if (mode == DEL)
		hashtable_delete(hashtable, name);
	else if (mode == ADD)
		hashtable_insert_replace(hashtable, new_var);
	else if (mode == FREE)
		hashtable_free(hashtable);
	return (hashtable);
}

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

char	**ft_split_env(char const *s)
{
	char		**array;
	char		*delim_pos;
	size_t		len;

	if (s == NULL)
		return (NULL);
	array = ft_calloc(3, sizeof(char *));
	if (array == NULL)
		return (NULL);
	delim_pos = ft_strchr(s, '=');
	len = delim_pos - s;
	array[0] = ft_calloc((len + 1), sizeof(char));
	if (array[0] == NULL)
		return (NULL);
	ft_strlcpy(array[0], s, len + 1);
	array[1] = ft_calloc((ft_strlen(delim_pos + 1) + 1), sizeof(char));
	if (array[1] == NULL)
		return (NULL);
	ft_strlcpy(array[1], delim_pos + 1, ft_strlen(delim_pos + 1) + 1);
	return (array);
}

t_env	*create_environ(char *name, char* value)
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

void	load_environ_hashtable(char *envp[])
{
	int		i;
	char	**env_content;
	t_env	*new_var;

	static_environ_htable(NULL, NULL, INIT);
	i = 0;
	while (envp[i])
	{
		env_content = ft_split_env(envp[i]);
		if (env_content == NULL)
			ft_handle_error("malloc failed");
		new_var = create_environ(env_content[0], env_content[1]);
		if (new_var == NULL)
		{
			free_matrix(env_content);
			ft_handle_error("malloc failed");
		}
		static_environ_htable(new_var, NULL, ADD);
		free_matrix(env_content);
		i++;
	}
	new_var = create_environ("?", "0");
	static_environ_htable(new_var, NULL, ADD);
}
