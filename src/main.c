/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/13 12:37:03 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signum;

int	main(int argc, char *argv[], char *envp[])
{
	char	*input; 
	char	**tokens;
	t_node	*ast;

	(void)argc;
	(void)argv;
	hashtable_load(envp);
	while (1)
	{
		set_signals_interactive_mode();
		input = prompt("$ ");
		if (!input)
		{
			input = strdup("exit");	
			break ;
		}
		tokens = tokenizer(input);
		ast = parser(tokens);
		static_ast_holder(ast, INIT);
		executor(ast);
		static_ast_holder(NULL, FREE);
//		break ;
	}
	hashtable_mx(NULL, NULL, FREE);
	rl_clear_history();
	return (last_exit_code(-1));
}
