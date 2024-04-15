/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:14:22 by mchamma           #+#    #+#             */
/*   Updated: 2024/04/14 22:10:31 by mchamma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset_call(t_cmd *cmd_node)
{
	t_list	*arg;
	int		befit;
	int		i;

	befit = 1;
	arg = (t_list *)cmd_node->cmd_args->next;
	while (arg)
	{
		i = 0;
		while (((char *)arg->content)[i]
			&& (ft_isalnum(((char *)arg->content)[i])
			|| ((char *)arg->content)[i] == '_'))
			i++;
		if (((char *)arg->content)[i])
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd((char *)arg->content, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			last_exit_code(1);
		}
		else
			hashtable_mx(NULL, (char *)arg->content, DEL);
		arg = arg->next;
	}
}
