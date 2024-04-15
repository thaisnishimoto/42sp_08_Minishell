/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:16:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/15 18:01:12 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_signals_interactive_mode(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_bzero(&sa_int, sizeof(sa_int));
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = &handle_display_new_prompt;
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	ft_bzero(&sa_int, sizeof(sa_quit));
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	set_signals_hdoc(pid_t pid)
{
	struct sigaction	sa_int;

	ft_bzero(&sa_int, sizeof(sa_int));
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
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
	sa.sa_flags = 0;
	if (pid == 0)
		sa.sa_handler = SIG_DFL;
	else
		sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
