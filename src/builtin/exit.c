/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:42:37 by mchamma           #+#    #+#             */
/*   Updated: 2024/04/12 21:24:17 by mchamma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	str_is_int(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	exit_call(t_cmd *cmd_node)
{
	t_list	*arg;
	int		exit_code;

	exit_code = -1;
	arg = (t_list *)cmd_node->cmd_args->next;
	printf("exit\n");
	if (arg && !str_is_int((char *)arg->content))
	{
		exit_code = 2;
		printf("bash: exit: %s: numeric argument required\n",
			(char *)arg->content);
	}
	else if (arg && arg->next)
		printf("bash: exit: too many arguments\n");
	else if (!arg || (arg && str_is_int((char *)arg->content)))
	{
		printf("\n");
		if (!arg)
			exit_code = 0;
		else
			exit_code = (ft_atoi((char *)arg->content) % 256)
				+ 256 * (1 - (ft_atoi((char *)arg->content) >= 0));
	}
	// printf("exit_code: %i\n", exit_code);
	return (exit_code);
}
