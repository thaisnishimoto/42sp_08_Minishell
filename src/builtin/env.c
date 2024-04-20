/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:30:22 by mchamma           #+#    #+#             */
/*   Updated: 2024/04/20 17:59:56 by tmina-ni         ###   ########.fr       */
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
		value = (hashtable_search(key[i]))->value;
		sign = (hashtable_search(key[i]))->sign;
		if (!ft_strcmp(sign, "="))
			ft_printf("%s%s%s\n", key[i], sign, value);
		i++;
	}
	ft_mtx_free(key);
}

void	env_call(t_cmd *cmd_node)
{
	t_list	*arg;

	last_exit_code(0);
	arg = (t_list *)cmd_node->cmd_args->next;
	if (!arg || !ft_strcmp((char *)arg->content, "")
		|| ((char *)arg->content)[0] == '#')
		env_print();
	else if (arg && ft_strcmp((char *)arg->content, "")
		&& ((char *)arg->content)[0] != '#')
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd((char *)arg->content, 2);
		ft_putendl_fd("': No such file or directory", 2);
		last_exit_code(127);
	}
}
