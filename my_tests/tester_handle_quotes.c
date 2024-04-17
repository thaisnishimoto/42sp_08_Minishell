/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_handle_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:14:57 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/17 00:22:54 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

int	g_signum;

int	main(int argc, char *argv[])
{
	char	*str;

	(void)argc;
	printf("arg: %s\n", argv[1]);
	str = process_quotes(ft_strdup(argv[1]));
	printf("handled arg: %s\n", str);
	free(str);
	return (0);
}
