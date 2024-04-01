/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/31 22:55:30 by tmina-ni         ###   ########.fr       */
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
	//print_hashtable(static_environ_htable(NULL, NULL, READ));
//	tokens = NULL;
//	ast = NULL; 
	while (1)
	{
		input = prompt();
		tokens = tokenizer(input);
		ast = parser(tokens);
		static_ast_holder(ast, INIT);
		static_ast_holder(NULL, READ);
		static_ast_holder(NULL, FREE);
//			executor(ast);
		//static_environ_htable(NULL, NULL, FREE);
		//break ;
	}
	return (0);
}
