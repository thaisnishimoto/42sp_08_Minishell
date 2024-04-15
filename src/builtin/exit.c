/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:42:37 by mchamma           #+#    #+#             */
/*   Updated: 2024/04/14 22:01:23 by mchamma          ###   ########.fr       */
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
	if (!str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i])
		return (0);
	return (1);
}

void	exit_call(t_cmd *cmd_node)
{
	t_list	*arg;

	arg = (t_list *)cmd_node->cmd_args->next;
	ft_putendl_fd("exit", 2);
	if ((arg && !str_is_int(arg->content) && arg
			&& ((char *)arg->content)[0] != '#')
			|| (arg && str_is_int(arg->content)
			&& ft_strlen(arg->content) > 19))
	{
		last_exit_code(2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg->content, 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (arg && arg->next)
	{
		last_exit_code(EXIT_FAILURE);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return ;
	}
	else if (arg && str_is_int(arg->content))
		last_exit_code(ft_atoi(arg->content) % 256
			+ 256 * (1 - (ft_atoi(arg->content) >= 0)));
	ft_free_exit();
}
