/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:16:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/13 23:25:29 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_display_new_prompt(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		last_exit_code(130);
	}
}

void	handle_hdoc_sigint(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
		g_signum = signum;
	}
}

void	handle_if_signaled(char *buffer, char *expected_eof, int hdoc_fd)
{
	if (g_signum == SIGINT)
	{
		close(hdoc_fd);
		ft_exit_child_process(130);
	}
	if (buffer == NULL)
	{
		close(hdoc_fd);
		last_exit_code(0);
		ft_putstr_fd("minishell: warning: here-document delimited by "
			"end-of-file (wanted '", 2);
		ft_putstr_fd(expected_eof, 2);
		ft_putendl_fd("')", 2);
	}
}
