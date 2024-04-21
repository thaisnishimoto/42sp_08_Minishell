/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:42:37 by mchamma           #+#    #+#             */
/*   Updated: 2024/04/21 12:16:46 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_int(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '0')
		i++;
	if (str[i] == '\0')
		return (1);
	if (str[0] == '-' && ft_strlen(str) <= 20)
		return (1);
	if (str[0] != '-' && ft_strlen(str) <= 19)
		return (1);
	return (0);
}

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

int	exit_call(t_cmd *cmd_node)
{
	t_list	*arg;

	arg = (t_list *)cmd_node->cmd_args->next;
	if (!arg || ((char *)arg->content)[0] == '#')
		return (1);
	else if ((arg && !str_is_int(arg->content) && ((char *)arg->content)[0] != '#')
			|| (arg && str_is_int(arg->content) && !check_int(arg->content)))
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
		return (0);
	}
	else if (arg && str_is_int(arg->content))
		last_exit_code(ft_atoi(arg->content) % 256
			+ 256 * (1 - (ft_atoi(arg->content) >= 0)));
	return (1);
}
