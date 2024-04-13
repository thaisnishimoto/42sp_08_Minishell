/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:16:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/13 10:35:47 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	signal_received(char *buffer, char *expected_eof, int hdoc_fd)
{
	if (g_signum == SIGINT)
	{
		close(hdoc_fd);
		ft_exit_child_process(130);
	}
	if (buffer == NULL)
	{
		close(hdoc_fd);
		ft_putstr_fd("minishell: warning: here-document delimited by "
			"end-of-file (wanted '", 2);
		ft_putstr_fd(expected_eof, 2);
		ft_putendl_fd("')", 2);
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

void	set_signals_hdoc(pid_t pid)
{
	struct sigaction	sa_int;

	ft_bzero(&sa_int, sizeof(sa_int));
	sigemptyset(&sa_int.sa_mask);
	if (pid == 0)
		sa_int.sa_handler = &handle_hdoc_sigint;
	else
		sa_int.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_int, NULL);
}

void	set_signals_exec_mode(pid_t pid)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	if (pid == 0)
		sa.sa_handler = SIG_DFL;
	else
		sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

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

void	set_signals_interactive_mode(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_bzero(&sa_int, sizeof(sa_int));
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = &handle_display_new_prompt;
	sigaction(SIGINT, &sa_int, NULL);
	ft_bzero(&sa_int, sizeof(sa_quit));
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
