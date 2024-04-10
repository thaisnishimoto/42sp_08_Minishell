/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:45:50 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/10 16:52:07 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//void	ft_handle_error(char *error_msg, t_data *pipex, t_fd *fd, int stage)
void	ft_handle_error(char *error_msg)
{
//	ft_free_pipex(pipex, fd, stage);
	static_environ_htable(NULL, NULL, FREE);
	perror(error_msg);
	exit(EXIT_FAILURE);
}
