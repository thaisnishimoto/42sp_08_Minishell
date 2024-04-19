/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_permission_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:15:00 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/19 18:58:17 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_exec_error(int exit_code, char *msg, char *cmd)
{
	last_exit_code(exit_code);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(msg, 2);
}

int	is_directory(char *pathname)
{
	struct stat	buff;

	stat(pathname, &buff);
	if (S_ISDIR(buff.st_mode))
		return (1);
	return (0);
}
