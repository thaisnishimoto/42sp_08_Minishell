/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:24:33 by mchamma           #+#    #+#             */
/*   Updated: 2024/04/12 18:54:06 by mchamma          ###   ########.fr       */
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
			path = arg->next->content;
		else if (!arg->next && home)
			path = home->value;
		if (path && chdir(path) == -1)
			printf("bash: cd: %s: No such file or directory\n", path);
		else if (!path)
			printf("bash: cd: HOME not set\n");
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
		printf("bash: cd: %s: No such file or directory\n",
			(char *)arg->next->content);
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
