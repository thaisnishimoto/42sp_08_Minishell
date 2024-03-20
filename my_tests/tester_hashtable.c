/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_hashtable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:11:21 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/20 11:48:35 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
//	t_env	**hashtable;
//
	(void)argc;
	(void)argv;
//	(void)envp;
//
//	hashtable = static_environ_htable(NULL, NULL, INIT);
//	t_env	var1 = {.name="PATH", .value="var1"};
//	t_env	var2 = {.name="USER", .value="var2"};
//	t_env	var3 = {.name="VAR3", .value="var3"};
//	t_env	var4 = {.name="VAR4", .value="var4"};
//	t_env	var5 = {.name="VAR5", .value="var5"};
//	t_env	var6 = {.name="VAR6", .value="var6"};
//	t_env	var7 = {.name="VAR7", .value="var7"};
//	t_env	var8 = {.name="VAR8", .value="var8"};
//	t_env	var9 = {.name="VAR9", .value="var9"};
//	t_env	var10 = {.name="VAR10", .value="var10"};
//	t_env	var11 = {.name="PATH", .value="var11"};
//	hashtable_insert_replace(hashtable, &var1);
//	hashtable_insert_replace(hashtable, &var2);
//	hashtable_insert_replace(hashtable, &var3);
//	hashtable_insert_replace(hashtable, &var4);
//	hashtable_insert_replace(hashtable, &var5);
//	hashtable_insert_replace(hashtable, &var6);
//	hashtable_insert_replace(hashtable, &var7);
//	hashtable_insert_replace(hashtable, &var8);
//	hashtable_insert_replace(hashtable, &var9);
//
//	print_hashtable(hashtable);
//
//	t_env	*find = hashtable_search(hashtable, "VAR10");
//	if (find)
//		printf("Found: %s\n", find->value);
//	else
//		printf("Not found\n");
//
//	hashtable_insert_replace(hashtable, &var10);
//	print_hashtable(hashtable);
//
//	find = hashtable_search(hashtable, "VAR10");
//	if (find)
//		printf("Found: %s\n", find->value);
//	else
//		printf("Not found\n");
//
//	hashtable_delete(hashtable, "VAR9");
//	print_hashtable(hashtable);
//	printf("Var 9 deleted\n");
//
//	hashtable_insert_replace(hashtable, &var11);
//	print_hashtable(hashtable);
//	printf("Var PATH updated to 11\n");

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
//	env[0] = "DISPLAY=:0";
//	env[1] = "_=/usr/bin/make";
//	env[2] = "TERM=xterm-256color";
//	env[3] = "WSL_DISTRO_NAME=Ubuntu";
//	env[4] = "XDG_RUNTIME_DIR=/mnt/wslg/runtime-dir";
//	env[5] = "USER=thaisnishimoto";
//	env[6] = "HOME=/home/thaisnishimoto";
//	env[7] = "MAKE_TERMERR=/dev/pts/1";
//	env[8] = "PAGER=less";
//	env[9] = "MAKELEVEL=1";
//	env[10] = "LS_COLORS=rs";
	
//	test_fixed_environ(env);
//	char *value = getenv("LS_COLOR");
//	printf("LS_COLOR=%s[end]\n", value);
//	value = getenv("LESSOPEN");
//	printf("LESSOPEN=%s[end]\n", value);
//	value = getenv("DISPLAY");
//	printf("DISPLAY=%s[end]\n", value);
//	test_n_environ(envp);
	test_environ(envp);

	return (0);
}
