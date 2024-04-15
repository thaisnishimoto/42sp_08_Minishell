/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:49:06 by mchamma           #+#    #+#             */
/*   Updated: 2024/04/14 21:57:10 by mchamma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	echo_check_option(t_list **arg)
{
	int		nline;
	int		i;

	nline = 1;
	while (*arg && ((char *)(*arg)->content)[0] == '-')
	{
		i = 1;
		while (((char *)(*arg)->content)[i] == 'n')
			i++;
		if (((char *)(*arg)->content)[i])
			break ;
		nline = 0;
		*arg = (*arg)->next;
	}
	return (nline);
}

void	echo_call(t_cmd *cmd_node)
{
	t_list	*arg;
	int		nline;

	arg = (t_list *)cmd_node->cmd_args->next;
	nline = echo_check_option(&arg);
	while (arg)
	{
		ft_putstr_fd((char *)arg->content, 2);
		if (arg->next)
			ft_putstr_fd(" ", 2);
		arg = arg->next;
	}
	if (nline)
		ft_putendl_fd("", 2);
}
