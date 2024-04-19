/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:15:00 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/19 14:20:51 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_exec_error(int exit_code, char *msg, char *cmd)
{
	last_exit_code(exit_code);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(msg, 2);
}

static int	is_directory(char *pathname)
{
	struct stat	buff;

	stat(pathname, &buff);
	if (S_ISDIR(buff.st_mode))
		return (1);
	return (0);
}

char	*validate_executable(char *pathname, char *cmd)
{
	if (!pathname || !*pathname || !ft_strncmp(cmd, "..", 3))
	{
		last_exit_code(127);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
	}
	else if (!ft_strncmp(cmd, ".", 2))
	{
		print_exec_error(2, ": filename argment required", cmd);
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
	}
	else if (access(pathname, F_OK) == -1)
		print_exec_error(127, ": No such file or directory", cmd);
	else if (pathname && access(pathname, X_OK) == -1)
		print_exec_error(126, ": Permission denied", cmd);
	else if (is_directory(pathname))
		print_exec_error(126, ": Is a directory", cmd);
	if (last_exit_code(-1) != 0)
	{
		free(pathname);
		pathname = NULL;
	}
	return (pathname);
}
