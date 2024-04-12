/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtx_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:26:00 by mchamma           #+#    #+#             */
/*   Updated: 2024/04/10 16:26:04 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_mtx_free(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
	{
		free (mtx[i]);
		i++;
	}
	free (mtx);
}