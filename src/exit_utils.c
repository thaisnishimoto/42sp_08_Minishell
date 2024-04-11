/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:45:50 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/11 15:37:09 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	last_exit_code(int new_value)
{
	static int	exit_code;

	if (new_value >= 0)
		exit_code = new_value;
	return (exit_code);
}

void	ft_handle_error(char *error_msg)
{
	static_environ_htable(NULL, NULL, FREE);
	perror(error_msg);
	exit(EXIT_FAILURE);
}
