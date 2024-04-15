/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:07:57 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/15 17:51:03 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_rm_trail_nl(char *str)
{
	int	len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str) - 1;
	if (str[len] == '\n')
		str[len] = '\0';
	return (str);
}

static void	change_input_stream_to_terminal(void)
{
	int		tty_fd;

	tty_fd = open("/dev/tty", O_RDWR);
	if (tty_fd < 0)
		ft_handle_error("open /dev/tty");
	if (dup2(tty_fd, STDIN_FILENO) == -1)
	{
		close(tty_fd);
		ft_handle_error("dup2");
	}
	close(tty_fd);
}

char	*prompt(char *symbol)
{
	char	*input;

	if (isatty(STDIN_FILENO))
		input = readline(symbol);
	else
	{
		input = ft_rm_trail_nl(ft_get_next_line(STDIN_FILENO));
		if (input == NULL)
			change_input_stream_to_terminal();
	}
	if (symbol[0] == '$')
	{
		if (input && *input && symbol[0] == '$')
			add_history(input);
		if (!input)
			input = strdup("exit");
		if (ft_strnstr(input, "exit", ft_strlen("exit"))
			&& !ft_strchr(input, '|'))
			ft_putendl_fd("exit", 2);
	}
	return (input);
}
