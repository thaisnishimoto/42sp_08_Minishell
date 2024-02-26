/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/02/26 17:25:40 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tree(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == REDIR)
	{
		printf("node type: %d\n", (t_redir)node->type);
		printf("redir file: %s\n", (t_redir)node->filename);
		print_tree(node->next_node);
	}
	else if (node->type == CMD)
	{
		printf("node type: %d\n", (t_cmd)node->type);
		printf("cmd pathname: %s\n", (t_cmd)node->pathname);
	}
}

t_node	*parse_cmd(t_node **tree_ptr, char *tokens[], int *i)
{
	t_cmd	*new_node;
	char	*operators = "<|>";

	node = malloc(sizeof(t_cmd));
	new_root->filename = malloc(ft_strlen(&tokens[*i][j]) + 1 * sizeof(char));
	ft_strlcpy(new_root->filename, &tokens[*i][j], ft_strlen(&tokens[*i][j]));
	new_root->next_node = tree_ptr;
}

void	parse_redir(t_redir **redirs_ptr, char *tokens[], int *i)
{
	t_redir	*new_redir;
	int	j;

	j = 0;
	new_redir = malloc(sizeof(t_redir));
	new_redir->type = REDIR;
	if (tokens[*i][j] == '<')
	{
		new_redir->fd = 0;
		new_redir->mode = O_RDONLY;
		j++;
	}
	else if (tokens[*i][j] == '>')
	{
		new_redir->fd = 1;
		j++;
		if (tokens[*i][j] == '>')
		{
			new_redir->mode = O_WRONLY|O_APPEND|O_CREAT;
			j++;
		}
		else
			new_redir->mode = O_WRONLY|O_TRUNC|O_CREAT;
	}
	if (tokens[*i][j] == '\0')
		(*i)++;
	new_redir->filename = malloc(ft_strlen(&tokens[*i][j]) + 1 * sizeof(char));
	ft_strlcpy(new_redir->filename, &tokens[*i][j], ft_strlen(&tokens[*i][j]));
	if (redirs_ptr == NULL)
		redirs_ptr = new_redir;
	else
	{
		while (redirs_ptr)
		{
			if (redirs_ptr->next_node == NULL)
			{
				redirs_ptr->next_node = new_redir;
				break ;
			}
			redirs_ptr = redirs_ptr->next_node;
		}
	}
	new_redir->next_node = NULL;
}

t_node	*parser(char *tokens[])
{
	int	i;
	t_node	*tree_ptr;
	t_redir	*redirs_ptr;
	char	*operators = "<|>";

	i = 0;
	redirs_ptr = NULL;
	tree_ptr = NULL;
	while (tokens[i])
	{
		if (ft_strchr(operators, tokens[i][0]))
			tree_ptr = parse_cmd(&redirs_ptr, tokens, &i);
		if (tokens[i][0] == '<' || tokens[i][0] == '>')
			parse_redir(&redirs_ptr, tokens, &i);
	}
	return (tree_ptr);
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
	t_node	*ast;

	tokens = NULL;
	ast = NULL; 
	while (1)
	{
		i = 0;
		input = readline("$ ");
		if (input && *input)
		{
			add_history(input);
			tokens = ft_strtok(input, ' ');
			ast = parser(tokens);
			print_tree(ast);
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
