/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_hashtable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:11:21 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/01 12:11:09 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	test_htable_operations(char *envp[])
{
	t_env	**hashtable;
	t_env	*find;

	hashtable = static_environ_htable(NULL, NULL, INIT);
	load_environ_hashtable(envp);

	t_env	var1 = {.name="VAR1", .value="var1_value"};
	t_env	var2 = {.name="VAR2", .value="var2_value"};
	t_env	var3 = {.name="VAR3", .value="var3_value"};
	t_env	var4 = {.name="VAR4", .value="var4_value"};
	t_env	var5 = {.name="VAR5", .value="var5_value"};
	t_env	var6 = {.name="HOME", .value="var6_value"};
	hashtable_insert_replace(hashtable, &var1);
	hashtable_insert_replace(hashtable, &var2);
	hashtable_insert_replace(hashtable, &var3);
	hashtable_insert_replace(hashtable, &var4);
	hashtable_insert_replace(hashtable, &var5);

	printf("\n**Init hashtable**\n");
	print_hashtable(hashtable);
	printf("\n**Search for existent variable VAR5**\n");
	find = hashtable_search(hashtable, "VAR5");
	if (find)
		printf("VAR5 found: %s\n", find->value);
	else
		printf("VAR5 not found\n");

	printf("\n**Delete existent variable VAR5**\n");
	printf("VAR5 table index = %d\n", hash_function("VAR5"));
	hashtable_delete(hashtable, "VAR5");
	print_hashtable(hashtable);

	printf("\n**Search for inexistent variable VAR5**\n");
	find = hashtable_search(hashtable, "VAR5");
	if (find)
		printf("VAR5 found: %s\n", find->value);
	else
		printf("VAR5 not found\n");

	printf("\n**Delete inexistent variable VAR5**\n");
	hashtable_delete(hashtable, "VAR5");

	printf("\n**Update existent variable HOME (index %d)**\n", hash_function("HOME"));
	hashtable_insert_replace(hashtable, &var6);
	print_hashtable(hashtable);
}

void	test_fixed_environ(char *envp[])
{
	t_env	**hashtable;

	load_environ_hashtable(envp);
	hashtable = static_environ_htable(NULL, NULL, READ);
	print_hashtable(hashtable);
	static_environ_htable(NULL, NULL, FREE);
	hashtable = static_environ_htable(NULL, NULL, READ);
	print_hashtable(hashtable);
}

void	test_n_environ(char *envp[])
{
	t_env	**hashtable;
	int	count;

	count = 0;
	while (envp[count])
	{
		printf("%d: %s\n", count, envp[count]);
		count++;
	}
	load_environ_hashtable(&envp[count - 12]);
	hashtable = static_environ_htable(NULL, NULL, READ);
	print_hashtable(hashtable);
	static_environ_htable(NULL, NULL, FREE);
	hashtable = static_environ_htable(NULL, NULL, READ);
	print_hashtable(hashtable);
}

void	test_environ(char *envp[])
{
	t_env	**hashtable;

	printf("\nTESTE TABLE ENVIRON\n");
	load_environ_hashtable(envp);
	hashtable = static_environ_htable(NULL, NULL, READ);
	print_hashtable(hashtable);
	static_environ_htable(NULL, NULL, FREE);
	hashtable = static_environ_htable(NULL, NULL, READ);
	print_hashtable(hashtable);
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;

	test_htable_operations(envp);

//	char	*env[13];
//	env[0] = "LINES=51";
//	env[1] = "HOSTTYPE=x86_64";
//	env[2] = "MFLAGS=";
//	env[3] = "GLIBCXX_FORCE_NEW=1";
//	env[4] = "MYVIMRC=/home/thaisnishimoto/.vimrc";
//	env[5] = "SHELL=/usr/bin/zsh";
//	env[6] = "WSL2_GUI_APPS_ENABLED=1";
//	env[7] = "PWD=/home/thaisnishimoto/42sp/Projects/8.Minishell/my_tests";
//	env[8] = "LD_PRELOAD=/usr/libexec/valgrind/vgpreload_core-amd64-linux.so:/usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so";
//	env[9] = "LS_COLORS=rs";
//	env[10] = "WSLENV=";
//	env[11] = "VIRTUAL_ENV_DISABLE_PROMPT=1";
//	env[12] = NULL;
//	test_fixed_environ(env);
//	char *value = getenv("LS_COLOR");
//	printf("LS_COLOR=%s[end]\n", value);

//	test_n_environ(envp);

//	test_environ(envp);

	return (0);
}
