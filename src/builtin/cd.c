/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:24:33 by mchamma           #+#    #+#             */
/*   Updated: 2024/04/14 21:57:16 by mchamma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


static void	cd_path(t_cmd *cmd_node)
{
	t_list	*arg;
	t_env	*home;
	char	*path;

	arg = (t_list *)cmd_node->cmd_args;
	home = hashtable_search("HOME");
	path = NULL;
	if (arg)
	{
		if (arg->next)
			path = (char *)arg->next->content;
		else if (!arg->next && home)
			path = home->value;
		if (path && chdir(path) == -1)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": No such file or directory", 2);
			last_exit_code(1);
		}
		else if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			last_exit_code(1);
		}
	}
}

void	cd_call(t_cmd *cmd_node)
{
	t_list	*arg;
	t_env	*newpwd;
	t_env	*oldpwd;
	char	*cwd;

	arg = (t_list *)cmd_node->cmd_args;
	if (arg->next && arg->next->next)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		last_exit_code(1);
		return ;
	}
	else if (arg || arg->next)
	{
		oldpwd = hashtable_create_node_type2("OLDPWD",
				hashtable_search("PWD")->value);
		hashtable_mx(oldpwd, NULL, ADD);
		cd_path(cmd_node);
		cwd = getcwd(NULL, 0);
		newpwd = hashtable_create_node_type2("PWD", cwd);
		hashtable_mx(newpwd, NULL, ADD);
		free(cwd);
	}
}
