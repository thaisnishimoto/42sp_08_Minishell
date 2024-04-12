/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:16:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/12 10:43:50 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//#include "../../include/minishel.h"

//void	sigint_handler(int signum)
//{
//	
//}

//void	init_signals()
//{
//	struct sigaction	sa_int;
//
////	sa_int.handler = &sigint_handler;
//	sa_int.sa_handler = SIG_IGN;
//	sigaction(SIGINT, &sa_int, NULL);
//}
//
////void	sigquit_handler(int signum)
////{
////
////}
//
//int	main(void)
//{
//	init_signals();
//	pid_t	pid;
//
//	pid = fork();
//	if (pid == 0)
//	{
//		while (1)
//		{
//			write(1, "child\n", 6);
//			sleep(3);
//		}
//	}
//	while (1)
//	{
//		write(1, "parent\n", 7);
//		sleep(3);
//	}
//	wait(NULL);
//}
