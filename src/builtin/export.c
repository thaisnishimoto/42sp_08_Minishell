/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:00:02 by mchamma           #+#    #+#             */
/*   Updated: 2024/04/21 15:31:47 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_print(t_list *arg)
{
	char	**key;
	char	*value;
	char	*sign;
	int		i;

	if (arg && arg->content)
		return ;
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

void	export_adjust_value(char **str)
{
	char	*temp;
	int		i;
	int		j;

	temp = ft_calloc(2 * ft_strlen(*str) + 1, sizeof(char));
	j = 0;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' || (*str)[i] == '\\' || (*str)[i] == '"')
			temp[j++] = '\\';
		temp[j++] = (*str)[i++];
	}
	temp[j] = '\0';
	free(*str);
	(*str) = ft_strdup(temp);
	free(temp);
}

void	export_condition_exec(t_list *arg)
{
	t_env	*temp;
	int		i;

	temp = hashtable_create_node_type1((char *)arg->content);
	export_adjust_value(&temp->value);
	i = 0;
	while (temp->key[i] && !ft_isdigit(temp->key[0])
		&& (ft_isalnum(temp->key[i]) || temp->key[i] == '_'))
		i++;
	if (temp->key[i])
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd((char *)arg->content, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		hashtable_free_node(temp);
		last_exit_code(1);
	}
	else
		hashtable_mx(temp, NULL, ADD);
}

int	export_condition_not_exec(t_list *arg)
{
	t_env	*temp;
	t_env	*temp2;
	int		result;

	result = 0;
	temp = hashtable_create_node_type1((char *)arg->content);
	export_adjust_value(&temp->value);
	temp2 = hashtable_search(temp->key);
	if ((ft_strcmp(temp->sign, "=") && temp2 && !ft_strcmp(temp2->sign, "="))
		|| !ft_strcmp(temp->key, "_"))
		result = 1;
	hashtable_free_node(temp);
	return (result);
}

void	export_call(t_cmd *cmd_node)
{
	t_list	*arg;

	last_exit_code(0);
	arg = (t_list *)cmd_node->cmd_args->next;
	export_print(arg);
	while (arg && arg->content)
	{
		if (export_condition_not_exec(arg))
			;
		else
			export_condition_exec(arg);
		arg = arg->next;
	}
}
