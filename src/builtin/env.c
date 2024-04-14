/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:30:22 by mchamma           #+#    #+#             */
/*   Updated: 2024/04/12 16:22:05 by mchamma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_print(void)
{
	char	**key;
	char	*value;
	char	*sign;
	int		i;

	key = hashtable_key_mtx();
	i = 0;
	while (key[i])
	{
		if (!ft_strcmp(key[i], "?"))
		{
			i++;
			continue ;
		}
		value = (hashtable_search(key[i]))->value;
		sign = (hashtable_search(key[i]))->sign;
		if (!ft_strcmp(sign, "="))
			printf("%s%s%s\n", key[i], sign, value);
		i++;
	}
	ft_mtx_free(key);
}

void	env_call(t_cmd *cmd_node)
{	
	t_list	*arg;

	arg = (t_list *)cmd_node->cmd_args->next;
	if (!arg || !ft_strcmp((char *)arg->content, "")
		|| ((char *)arg->content)[0] == '#')
		env_print();
	else if (arg && ft_strcmp((char *)arg->content, "")
		&& ((char *)arg->content)[0] != '#')
		ft_printf("env: %s: No such file or directory\n",
			(char *)arg->content);
}
