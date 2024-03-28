/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/28 11:46:46 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tree(t_node *node)
{
	if (node == NULL)
		return ;
	printf("\n");
	if (node->type == PIPE)
	{
		t_pipe	*pipe_node = (t_pipe *)node;
		printf("->node type: PIPE(%d)\n", pipe_node->type);
		printf("\n---LEFT OF PIPE---");
		print_tree((t_node *)pipe_node->left);
		printf("\n---RIGHT OF PIPE---");
		print_tree((t_node *)pipe_node->right);
	}
	else if (node->type == REDIR)
	{
		t_redir	*redir_node = (t_redir *)node;
		printf("->node type: REDIR(%d)\n", redir_node->type);
		printf("fd redir: %d\n", redir_node->fd);
		printf("redir file: %s\n", redir_node->filename);
		print_tree((t_node *)redir_node->next);
	}
	else if (node->type == HEREDOC)
	{
		t_redir	*redir_node = (t_redir *)node;
		printf("->node type: HEREDOC(%d)\n", redir_node->type);
		printf("redir delim: %s\n", redir_node->eof);
		print_tree((t_node *)redir_node->next);
	}
	else if (node->type == CMD)
	{
		t_cmd	*cmd_node = (t_cmd *)node;
		t_list	*temp = cmd_node->cmd_args;
		printf("->node type: CMD(%d)\n", cmd_node->type);
		int	i = 0;
		while (temp)
		{
			printf("cmd arg[%d]: %s\n", i, (char *)temp->content);
			temp = temp->next;
		}
		print_tree((t_node *)cmd_node->redirs);
	}
}

t_node	*build_tree_branch(t_cmd *cmd_node, t_redir *redirs_ptr)
{
	if (!cmd_node)
		return ((t_node *)redirs_ptr);
	else
	{
		cmd_node->redirs = redirs_ptr;
		return ((t_node *)cmd_node);
	}
}

t_node	*parser(char *tokens[])
{
	int	i;
	t_node	*tree_ptr;
	t_redir	*redirs_ptr;
	t_cmd	*cmd_node;
	
	i = 0;
	tree_ptr = NULL;
	redirs_ptr = NULL;
	cmd_node = NULL;
	while (tokens[i])
	{
		if (!ft_strchr("<|>", tokens[i][0]))
			parse_cmd(&cmd_node, tokens, &i);
		else if (tokens[i][0] == '<' || tokens[i][0] == '>')
			parse_redir(&redirs_ptr, tokens, &i);
		else if (tokens[i][0] == '|')
		{
			tree_ptr = build_tree_branch(cmd_node, redirs_ptr);
			tree_ptr = parse_pipe(tree_ptr, parser(&tokens[++i]));
			break ;
		}
	}
	if (!tree_ptr)
		tree_ptr = build_tree_branch(cmd_node, redirs_ptr);
	return (tree_ptr);
}

char	*ft_rm_trail_nl(char *str)
{
	int	len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str) - 1;
	if (str[len] == '\n')
		str[len] = '\0';
	return (str);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input; 
	char	**tokens;
	t_node	*ast;

	(void)argc;
	(void)argv;
	load_environ_hashtable(envp);
	//print_hashtable(static_environ_htable(NULL, NULL, READ));
	tokens = NULL;
	ast = NULL; 
	while (1)
	{
 		if (isatty(STDIN_FILENO))
			input = readline("$ ");
		else
		{
			input = ft_rm_trail_nl(ft_get_next_line(STDIN_FILENO));
			int	tty_fd = open("/dev/tty", O_RDWR);
        		if (tty_fd < 0)
			{
            			perror("open /dev/tty");
            			exit(EXIT_FAILURE);
			}
			if (dup2(tty_fd, STDIN_FILENO) == -1)
			{
            			perror("dup2");
            			exit(EXIT_FAILURE);
        		}
			close(tty_fd);
		}
		if (input && *input)
		{
			add_history(input);
			tokens = ft_strtok(input, ' ');
			if (tokens == NULL)
			{
				free(input);
				return (1);
			}
//			int	j = 0;
//			while (tokens[j])
//			{
//				printf("token[%d]: %s\n", j, tokens[j]);
//				j++;
//			}
			ast = parser(tokens);
//			print_tree(ast);
			executor(ast);
			input = NULL;
		}
//		break ;
	}
	return (0);
}
