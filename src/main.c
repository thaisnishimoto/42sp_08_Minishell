/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/02/16 18:21:20 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//int	main(int argc, char *argv[], char *envp[])
int	main(void)
{
	while (1)
	{
		char	*line; 

		line = readline("$ ");
		if (line && *line)
		{
			add_history(line);
			free(line);
			line = NULL;
		}
	}
	return (0);
}
