/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:15:00 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/19 17:47:47 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*parse_arg_trim_quotes(char *token)
{
	char	**token_substr;
	int		i;

	if (token == NULL)
		return (NULL);
	if (token[0] == '\0')
		return (token);
	token_substr = ft_split_concat_token(token);
	if (token_substr == NULL)
		return (NULL);
	i = 0;
	while (token_substr[i])
	{
		token_substr[i] = ft_trim_quotes(token_substr[i], "\"\'");
		if (token_substr[i] == NULL)
		{
			ft_free_matrix(token_substr);
			return (NULL);
		}
		i++;
	}
	return (ft_rejoin_substr(token_substr));
}

t_list	*processs_args(t_list **cmd_args)
{
	char	**token_mtx;
	char	*temp;
	int		i;
	t_list	*list_args;
	t_list	*xtemp;
	t_list	*new_arg;

	if (cmd_args == NULL)
		return (NULL);
	xtemp = *cmd_args;
	list_args = NULL;
	while (xtemp)
	{
		if (ft_strchr(xtemp->content, '\"') || ft_strchr(xtemp->content, '\''))
		{
			temp = parse_arg_trim_quotes(ft_strdup(xtemp->content));
			new_arg = ft_lstnew(temp);
			if (new_arg == NULL)
				return (NULL);
			ft_lstadd_back(&list_args, new_arg);
		}
		else
		{
			token_mtx = ft_split(xtemp->content, ' ');
			if (token_mtx == NULL)
				return (NULL);
			i = 0;
			while (token_mtx[i])
			{
				new_arg = ft_lstnew(ft_strdup(token_mtx[i]));
				if (new_arg == NULL)
					return (NULL);
				ft_lstadd_back(&list_args, new_arg);
				i++;
			}
			ft_free_matrix(token_mtx);
		}
		xtemp = xtemp->next;
	}
	ft_lstclear(cmd_args, free);
	*cmd_args = list_args;
	return (*cmd_args);
}

static char	**create_cmd_arg_vector(t_list *cmd_args)
{
	t_list	*temp;
	char	**cmd_argv;
	int		count;
	int		i;

	temp = cmd_args;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	cmd_argv = ft_calloc(count + 1, sizeof(char *));
	i = 0;
	while (i < count)
	{
		cmd_argv[i] = ft_strdup((char *)cmd_args->content);
		i++;
		cmd_args = cmd_args->next;
	}
	return (cmd_argv);
}

static char	**get_path(void)
{
	char	*path_value;
	char	**path;
	char	*temp;
	int		i;

	path_value = NULL;
	path = NULL;
	if (hashtable_search("PATH"))
		path_value = hashtable_search("PATH")->value;
	if (path_value)
		path = ft_split(path_value, ':');
	i = 0;
	while (path && path[i])
	{
		temp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = ft_strdup(temp);
		free(temp);
		i++;
	}
	return (path);
}

static char	*get_pathname(char *cmd, char *path[])
{
	char	*pathname;
	int		i;

	pathname = NULL;
	if (cmd[0] == '\0' || cmd[0] == '/' || cmd[0] == '.')
		pathname = ft_strdup(cmd);
	else
	{
		if (path == NULL)
			return (ft_strdup(cmd));
		i = -1;
		while (path[++i])
		{
			last_exit_code(0);
			pathname = ft_strjoin(path[i], cmd);
			if (access(pathname, F_OK) == -1)
			{
				free(pathname);
				pathname = NULL;
			}
			else
				break ;
		}
	}
	return (pathname);
}

void	exec_cmd(t_list *cmd_args)
{
	char	**envp;
	char	**cmd_argv;
	char	*pathname;
	char	**path;

	if (cmd_args == NULL)
		return ;
	envp = hashtable_envp_mtx();
	cmd_argv = create_cmd_arg_vector(cmd_args);
	path = get_path();
	pathname = get_pathname(cmd_argv[0], path);
	pathname = validate_executable(pathname, cmd_argv[0]);
	if (pathname)
	{
		execve(pathname, cmd_argv, envp);
		perror("execve failed");
		free(pathname);
		last_exit_code(EXIT_FAILURE);
	}
	ft_free_matrix(envp);
	ft_free_matrix(cmd_argv);
	if (path)
		ft_free_matrix(path);
}
