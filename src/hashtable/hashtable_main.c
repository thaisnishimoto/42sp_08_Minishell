/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:25:04 by mchamma           #+#    #+#             */
/*   Updated: 2024/04/12 19:31:56 by mchamma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	**hashtable_mx(t_env *new, char *key, int mode)
{
	static t_env	*hash[TABLE_SIZE];

	if (mode == INIT)
		hashtable_init(hash);
	else if (mode == DEL)
		hashtable_delete(hash, key);
	else if (mode == ADD)
		hashtable_insert_replace(hash, new);
	else if (mode == FREE)
		hashtable_free_hash(hash);
	else if (mode == PRINT)
		hashtable_print(hash);
	return (hash);
}

char	**split_env(char *str)
{
	char		**tkn;
	char		*delim_pos;
	size_t		len;

	if (str == NULL)
		return (NULL);
	tkn = ft_calloc(3 + 1, sizeof(char *));
	if (str[0] == '=' || !ft_strchr(str, '='))
	{
		tkn[0] = ft_strdup(str);
		return (tkn);
	}
	delim_pos = ft_strchr(str, '=');
	len = delim_pos - str;
	tkn[0] = ft_calloc((len + 1), sizeof(char));
	ft_strlcpy(tkn[0], str, len + 1);
	tkn[1] = ft_strdup("=");
	tkn[2] = ft_calloc((ft_strlen(delim_pos + 1) + 1), sizeof(char));
	ft_strlcpy(tkn[2], delim_pos + 1, ft_strlen(delim_pos + 1) + 1);
	return (tkn);
}

t_env	*hashtable_create_node_type2(char *key, char *value)
{
	t_env	*new;

	if (!key)
		return (NULL);
	new = ft_calloc(1, sizeof(t_env));
	if (key)
		new->key = ft_strdup(key);
	new->sign = ft_strdup("=");
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = ft_strdup("");
	new->next = NULL;
	return (new);
}

t_env	*hashtable_create_node_type1(char *env)
{
	char	**tkn;
	t_env	*new;

	if (!env)
		return (NULL);
	tkn = split_env(env);
	new = ft_calloc(1, sizeof(t_env));
	if (tkn[0])
		new->key = ft_strdup(tkn[0]);
	if (tkn[1])
		new->sign = ft_strdup(tkn[1]);
	else
		new->sign = ft_strdup("");
	if (tkn[2])
		new->value = ft_strdup(tkn[2]);
	else
		new->value = ft_strdup("");
	ft_mtx_free(tkn);
	new->next = NULL;
	return (new);
}

void	hashtable_load(char **envp)
{
	t_env	*new;
	int		i;

	hashtable_mx(NULL, NULL, INIT);
	i = 0;
	while (envp[i])
	{
		new = hashtable_create_node_type1(envp[i]);
		hashtable_mx(new, NULL, ADD);
		i++;
	}
}
