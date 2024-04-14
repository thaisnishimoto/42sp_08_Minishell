/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:54:42 by mchamma           #+#    #+#             */
/*   Updated: 2024/04/12 19:30:07 by mchamma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_print(void)
{
	char	**key;
	char	*value;
	char	*sign;
	int		i;

	key = hashtable_key_mtx_sorted();
	i = 0;
	while (key[i])
	{
		value = (hashtable_search(key[i]))->value;
		sign = (hashtable_search(key[i]))->sign;
		if (ft_strcmp(key[i], "_") && !ft_strcmp(sign, "="))
			printf("declare -x %s%s\"%s\"\n", key[i], sign, value);
		else if (ft_strcmp(key[i], "_") && ft_strcmp(sign, "="))
			printf("declare -x %s\n", key[i]);
		i++;
	}
	ft_free_matrix(key);
}

void	export_env_adjust_value(char **str)
{
	char	*temp;
	int		i;
	int		j;

	temp = ft_calloc(2 * ft_strlen(*str) + 1, sizeof(char));
	j = 0;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' )
			temp[j++] = '\\';
		temp[j++] = (*str)[i++];
	}
	temp[j] = '\0';
	free(*str);
	(*str) = ft_strdup(temp);
	free(temp);
}

void	export_check_print(t_cmd *cmd_node)
{
	t_list	*arg;

	arg = (t_list *)cmd_node->cmd_args->next;
	if (!arg || !ft_strcmp((char *)arg->content, "")
		|| ((char *)arg->content)[0] == '#')
		export_print();
}

void	export_call(t_cmd *cmd_node)
{
	t_list	*arg;
	t_env	*tmp;
	int		i;

	arg = (t_list *)cmd_node->cmd_args->next;
	export_check_print(cmd_node);
	while (arg && ft_strcmp((char *)arg->content, "")
		&& ((char *)arg->content)[0] != '#')
	{
		tmp = hashtable_create_node_type1((char *)arg->content);
		export_env_adjust_value(&tmp->value);
		i = 0;
		while (tmp->key[i] && (ft_isalnum(tmp->key[i]) || tmp->key[i] == '_'))
			i++;
		if (tmp->key[i])
		{
			printf("bash: export: '%s': not a valid identifier\n",
				(char *)arg->content);
			hashtable_free_node(tmp);
		}
		else
			hashtable_mx(tmp, NULL, ADD);
		arg = arg->next;
	}
}
