/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:15:00 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/07 23:23:10 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_path(void)
{
	char	*path_value;
	char	**path;
	char	*temp;
	int		i;

	path = NULL;
	path_value = ft_getenv("PATH");
	if (path_value)
	{
		path = ft_split(path_value, ':');
		free(path_value);
	}
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

char	*find_pathname(char **path, char *cmd)
{
	int		i;
	char	*pathname;

	if (cmd[0] == '/' || cmd[0] == '.')
		pathname = ft_strdup(cmd);
	else
	{
		i = 0;
		while (path[i])
		{
			update_exit_code(0);
			pathname = ft_strjoin(path[i], cmd);
			if (access(pathname, F_OK) == -1)
			{
				update_exit_code(127);
				free(pathname);
				pathname = NULL;
				i++;
			}
			else
				break ;
		}
	}
	return (pathname);
}

char	*search_executable(char *cmd)
{
	char	**path;
	char	*pathname;

	if (*cmd == '\0')
	{
		update_exit_code(127);
		return (NULL);
	}
	path = get_path();
	pathname = find_pathname(path, cmd);
	if (pathname && access(pathname, X_OK) == -1)
	{
		update_exit_code(126);
		free(pathname);
		pathname = NULL;
	}
	free_matrix(path);
	return (pathname);
}

char	**create_cmd_arg_vector(t_list *cmd_args)
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

void	exec_cmd(t_list *cmd_args)
{
	char	**cmd_argv;
	char	*pathname;

	cmd_argv = create_cmd_arg_vector(cmd_args);
	pathname = search_executable(cmd_argv[0]);
	if (pathname != NULL)
	{
		execve(pathname, cmd_argv, NULL);
		free(pathname);
		update_exit_code(-1);
	}
	free_matrix(cmd_argv);
	exit (get_exit_code());
}
