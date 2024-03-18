/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_hashtable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:11:21 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/12 22:52:17 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	test_environ(char *envp[])
{
	t_env	**hashtable;

	printf("TESTE TABLE ENVIRON\n");
	load_environ_hashtable(envp);
	hashtable = static_environ_htable(NULL, NULL, READ);
	print_hashtable(hashtable);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env	*hashtable[TABLE_SIZE];

	(void)argc;
	(void)argv;
	init_hashtable(hashtable);
	t_env	var1 = {.name="PATH", .value="var1"};
	t_env	var2 = {.name="USER", .value="var2"};
	t_env	var3 = {.name="VAR3", .value="var3"};
	t_env	var4 = {.name="VAR4", .value="var4"};
	t_env	var5 = {.name="VAR5", .value="var5"};
	t_env	var6 = {.name="VAR6", .value="var6"};
	t_env	var7 = {.name="VAR7", .value="var7"};
	t_env	var8 = {.name="VAR8", .value="var8"};
	t_env	var9 = {.name="VAR9", .value="var9"};
	t_env	var10 = {.name="VAR10", .value="var10"};
	t_env	var11 = {.name="PATH", .value="var11"};
	hashtable_insert_replace(hashtable, &var1);
	hashtable_insert_replace(hashtable, &var2);
	hashtable_insert_replace(hashtable, &var3);
	hashtable_insert_replace(hashtable, &var4);
	hashtable_insert_replace(hashtable, &var5);
	hashtable_insert_replace(hashtable, &var6);
	hashtable_insert_replace(hashtable, &var7);
	hashtable_insert_replace(hashtable, &var8);
	hashtable_insert_replace(hashtable, &var9);

	print_hashtable(hashtable);

	t_env	*find = hashtable_search(hashtable, "VAR10");
	if (find)
		printf("Found: %s\n", find->value);
	else
		printf("Not found\n");

	hashtable_insert(hashtable, &var10);
	print_hashtable(hashtable);

	find = hashtable_search(hashtable, "VAR10");
	if (find)
		printf("Found: %s\n", find->value);
	else
		printf("Not found\n");

	hashtable_delete(hashtable, "VAR9");
	print_hashtable(hashtable);
	printf("Var 9 deleted\n");

	hashtable_insert_replace(hashtable, &var11);
	print_hashtable(hashtable);
	printf("Var PATH updated to 11\n");

	test_environ(envp);

	return (0);
}
