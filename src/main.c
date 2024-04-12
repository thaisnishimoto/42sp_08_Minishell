/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/12 15:21:34 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	set_signal_handler(void)
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
int	main(int argc, char *argv[], char *envp[])
{
	char	*input; 
	char	**tokens;
	t_node	*ast;

	(void)argc;
	(void)argv;
	set_signal_handler();
	hashtable_load(envp);
	//static_environ_htable(NULL, NULL, PRINT);
//	tokens = NULL;
//	ast = NULL; 
	while (1)
	{
		input = prompt("$ ");
		if (!input)
			input = strdup("exit");	
		tokens = tokenizer(input);
		ast = parser(tokens);
		static_ast_holder(ast, INIT);
//		static_ast_holder(NULL, PRINT);
		executor(ast);
		static_ast_holder(NULL, FREE);
		break ;
	}
	hashtable_mx(NULL, NULL, FREE);
	rl_clear_history();
	return (last_exit_code(-1));
}
