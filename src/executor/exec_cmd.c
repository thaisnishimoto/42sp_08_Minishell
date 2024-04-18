/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:15:00 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/18 19:08:58 by mchamma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**create_cmd_arg_vector(t_list *cmd_args)
{
	t_list	*temp;
	char	**cmd_argv;
	int		count;
	int		i;

	temp = cmd_args;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	cmd_argv = ft_calloc(count + 1, sizeof(char *));
	i = 0;
	while (i < count)
	{
		cmd_argv[i] = ft_strdup((char *)cmd_args->content);
		i++;
		cmd_args = cmd_args->next;
	}
	return (cmd_argv);
}

static char	**get_path(void)
{
	char	*path_value;
	char	**path;
	char	*temp;
	int		i;

	path_value = NULL;
	path = NULL;
	if (hashtable_search("PATH"))
		path_value = hashtable_search("PATH")->value;
	if (path_value)
		path = ft_split(path_value, ':');
	i = 0;
	while (path && path[i])
	{
		temp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = ft_strdup(temp);
		free(temp);
		i++;
	}
	return (path);
}

static char	*get_pathname(char *cmd, char *path[])
{
	char	*pathname;
	int		i;

	pathname = NULL;
	if (cmd[0] == '\0' || cmd[0] == '/' || cmd[0] == '.')
		pathname = ft_strdup(cmd);
	else
	{
		if (path == NULL)
			return (ft_strdup(cmd));
		i = -1;
		while (path[++i])
		{
			last_exit_code(0);
			pathname = ft_strjoin(path[i], cmd);
			if (access(pathname, F_OK) == -1)
			{
				free(pathname);
				pathname = NULL;
			}
			else
				break ;
		}
	}
	return (pathname);
}

void	exec_cmd(t_list *cmd_args)
{
	char	**envp;
	char	**cmd_argv;
	char	*pathname;
	char	**path;

	if (cmd_args == NULL)
		return ;
	envp = hashtable_envp_mtx();
	cmd_argv = create_cmd_arg_vector(cmd_args);
	path = get_path();
	pathname = get_pathname(cmd_argv[0], path);
	pathname = validate_executable(pathname, cmd_argv[0]);
	if (pathname)
	{
		execve(pathname, cmd_argv, envp);
		perror("execve failed");
		free(pathname);
		last_exit_code(EXIT_FAILURE);
	}
	ft_free_matrix(envp);
	ft_free_matrix(cmd_argv);
	if (path)
		ft_free_matrix(path);
}
