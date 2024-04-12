/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/11 17:56:32 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*input; 
	char	**tokens;
	t_node	*ast;

	(void)argc;
	(void)argv;
	load_environ_hashtable(envp);
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
	static_environ_htable(NULL, NULL, FREE);
	rl_clear_history();
	return (last_exit_code(-1));
}
