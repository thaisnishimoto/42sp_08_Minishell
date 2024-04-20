/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:10:46 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/20 18:54:20 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_cmd *cmd_node)
{
	if (cmd_node->cmd_args == NULL)
		return (0);
	else if (!ft_strcmp("cd", cmd_node->cmd_args->content))
		return (1);
	else if (!ft_strcmp("echo", cmd_node->cmd_args->content))
		return (1);
	else if (!ft_strcmp("env", cmd_node->cmd_args->content))
		return (1);
	else if (!ft_strcmp("exit", cmd_node->cmd_args->content))
		return (1);
	else if (!ft_strcmp("export", cmd_node->cmd_args->content))
		return (1);
	else if (!ft_strcmp("pwd", cmd_node->cmd_args->content))
		return (1);
	else if (!ft_strcmp("unset", cmd_node->cmd_args->content))
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd_node)
{
	if (!ft_strcmp("cd", cmd_node->cmd_args->content))
		cd_call(cmd_node);
	else if (!ft_strcmp("echo", cmd_node->cmd_args->content))
		echo_call(cmd_node);
	else if (!ft_strcmp("env", cmd_node->cmd_args->content))
		env_call(cmd_node);
	else if (!ft_strcmp("exit", cmd_node->cmd_args->content))
		return (exit_call(cmd_node));
	else if (!ft_strcmp("export", cmd_node->cmd_args->content))
		export_call(cmd_node);
	else if (!ft_strcmp("pwd", cmd_node->cmd_args->content))
		pwd_call();
	else if (!ft_strcmp("unset", cmd_node->cmd_args->content))
		unset_call(cmd_node);
	return (0);
}
