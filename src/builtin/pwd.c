/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:01:55 by mchamma           #+#    #+#             */
/*   Updated: 2024/04/15 13:12:10 by mchamma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd_call(void)
{
	char	*cwd;

	last_exit_code(0);
	cwd = getcwd(NULL, 0);
	if (cwd)
		ft_putendl_fd(cwd, 2);
	free(cwd);
}
