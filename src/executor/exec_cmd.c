/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:15:00 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/15 14:45:53 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**get_path(void)
{
	char	*path_value;
	char	**path;
	char	*temp;
	int		i;

	path = NULL;
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

static char	*find_pathname(char **path, char *cmd)
{
	int		i;
	char	*pathname;

	pathname = NULL;
	if (*cmd == '\0')
		last_exit_code(127);
	else if (cmd[0] == '/' || cmd[0] == '.')
		pathname = ft_strdup(cmd);
	else
	{
		i = -1;
		while (path[++i])
		{
			last_exit_code(0);
			pathname = ft_strjoin(path[i], cmd);
			if (access(pathname, F_OK) == -1)
			{
				last_exit_code(127);
				free(pathname);
				pathname = NULL;
			}
			else
				break ;
		}
	}
	return (pathname);
}

static char	*search_executable(char *cmd)
{
	char	**path;
	char	*pathname;

	path = get_path();
	pathname = find_pathname(path, cmd);
	if (last_exit_code(-1) == 127)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
	}
	else if (pathname && access(pathname, X_OK) == -1)
	{
		last_exit_code(126);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Permission denied", 2);
		free(pathname);
		pathname = NULL;
	}
	ft_free_matrix(path);
	return (pathname);
}

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

void	exec_cmd(t_list *cmd_args)
{
	char	**envp;
	char	**cmd_argv;
	char	*pathname;

	if (cmd_args == NULL)
		return ;
	envp = hashtable_envp_mtx();
	cmd_argv = create_cmd_arg_vector(cmd_args);
	pathname = search_executable(cmd_argv[0]);
	if (pathname != NULL)
	{
		execve(pathname, cmd_argv, envp);
		perror("execve failed");
		free(pathname);
		last_exit_code(EXIT_FAILURE);
	}
	ft_free_matrix(cmd_argv);
	ft_free_matrix(envp);
}
