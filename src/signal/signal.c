/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:16:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/12 17:47:11 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_hdoc_ctrl_d(char *expected_eof)
{
	ft_putstr_fd("minishell: warning: here-document delimited by "
		"end-of-file (wanted '", 2);
	ft_putstr_fd(expected_eof, 2);
	ft_putendl_fd("')", 2);
}

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sigint_handler2(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "new sighandler", 14);
	}
}

void	set_hdoc_signal(pid_t pid)
{
	struct sigaction	sa_int;

	if (pid == 0)
	{
		ft_bzero(&sa_int, sizeof(sa_int));
		sigemptyset(&sa_int.sa_mask);
		//sa_int.sa_handler = SIG_DFL;
		sa_int.sa_handler = &sigint_handler2;
		sigaction(SIGINT, &sa_int, NULL);
	}
}

void	init_signal(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_bzero(&sa_int, sizeof(sa_int));
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = &sigint_handler;
	sigaction(SIGINT, &sa_int, NULL);
	ft_bzero(&sa_int, sizeof(sa_quit));
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
