/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/02/26 01:11:45 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*parse_redir(char *tokens[], int i)
{
	t_redir	*node;
	int	j;

	j = 0;
	node = malloc(sizeof(t_redir));
	node->type = REDIR;
	if (tokens[i][j] == '<')
	{
		node->fd = 0;
		node->mode = O_RDONLY;
		j++;
	}
	if (tokens[i][j] == '>')
	{
		node->fd = 1;
		j++;
		if (tokens[i][j] == '>')
			node->mode = O_WRONLY|O_APPEND|O_CREAT;
		else
			node->mode = O_WRONLY|O_TRUNC|O_CREAT;
	}
	if (tokens[i][1] == '<')
}

t_tree	*parser(char *tokens[])
{
	int	i;

	i = 0;
	if (tokens[i][0] == '<' || tokens[i][0] == '>')
		parse_redir(tokens, i);
}

size_t	preserve_quoted_substr(char *str)
{
	size_t	len;

	len = 0;
	if (str[len] == '\'')
	{
		len++;
		while (str[len] != '\'')
			len++;
		len++;
	}
 	else if (str[len] == '\"')
	{
		len++;
		while (str[len] != '\"')
			len++;
		len++;
	}
	return (len);
}

int	ft_count_tokens(char *str, char delim)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == delim)
			i++;
		if (str[i] != '\0')
			count++;
		if (str[i] == '\'' || str[i] == '\"')
			i += preserve_quoted_substr(&str[i]);
		while (str[i] && str[i] != delim)
			i++;
	}
	return (count);
}

char	**ft_strtok(char *input, char delim)
{
	int	tok_count;
	int	i;
	int	j;
	char	**tokens;

	tok_count = ft_count_tokens(input, delim);
	i = 0;
	j = 0;
	tokens = malloc((tok_count + 1) * sizeof(char *));
//	if (tokens == NULL)
//		exit(EXIT_FAILURE);
	tokens[tok_count] = NULL;
	while (j < tok_count)
	{
		while (input[i] == delim)
			i++;
		tokens[j] = &input[i];
		j++;
		if (input[i] == '\'' || input[i] == '\"')
			i += preserve_quoted_substr(&input[i]);
		while (input[i] && input[i] != delim)
			i++;
	}
	j = 0;
	while (j < tok_count)
	{
		i = 0;
		if (tokens[j][i] == '\'' || tokens[j][i] == '\"')
			i += preserve_quoted_substr(tokens[j]);
		while (tokens[j][i] != delim)
			i++;
		tokens[j][i] = '\0';
		printf("token[%d]: %s\n", j, tokens[j]);
		j++;
	}
	return (tokens);
}

//int	main(int argc, char *argv[], char *envp[])
int	main(void)
{
	char	*input; 
	char	**tokens;
	int	i;

	tokens = NULL; 
	while (1)
	{
		i = 0;
		input = readline("$ ");
		if (input && *input)
		{
			add_history(input);
			tokens = ft_strtok(input, ' ');
			parser(tokens);
		//	while (tokens[i])
		//	{
		//		printf("tokens: %s\n", tokens[i]);
		//		i++;
		//	}
			free(input);
			input = NULL;
		}
	}
	return (0);
}
