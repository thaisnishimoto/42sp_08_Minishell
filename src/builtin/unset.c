/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:14:22 by mchamma           #+#    #+#             */
/*   Updated: 2024/04/12 17:26:45 by mchamma          ###   ########.fr       */
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
		while (((char *)arg->content)[i])
		{
			if (!(ft_isalnum(((char *)arg->content)[i])
				&& ((char *)arg->content)[i] != '_'))
				befit = 0;
			i++;
		}
		if (befit == 1)
			hashtable_mx(NULL, (char *)arg->content, DEL);
		else
			printf("bash: unset: '%s': not a valid identifier",
				(char *)arg->content);
		arg = arg->next;
	}
}
