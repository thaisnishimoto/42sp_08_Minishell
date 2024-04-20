/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:45:50 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/20 18:24:32 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	last_exit_code(int new_value)
{
	static int	exit_code;

	if (new_value >= 0)
		exit_code = new_value;
	return (exit_code);
}

void	ft_handle_error(char *error_msg)
{
	hashtable_mx(NULL, NULL, FREE);
	perror(error_msg);
	exit(EXIT_FAILURE);
}

void	ft_free_exit(void)
{
	hashtable_mx(NULL, NULL, FREE);
	static_ast_holder(NULL, FREE);
	rl_clear_history();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit (last_exit_code(-1));
}
