/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_environ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:41 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/03/18 13:42:59 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minunit.h"
#include "../include/minishell.h"
#include <stdio.h> //popen

/*
FILE *popen(const char *command, const char *type);
opens a process stream with fork and invokes the shell cmd
type r: we read command's output (receive)

char *fgets (char *str, int n, FILE *stream);
reads from stream and stores in str, until n-1 chars, \n, EOF
*/

char	*exec_command(char *cmd)
{
	int	line_len;
	FILE	*stream;
	char	*output;

	line_len = 0;
	output = ft_calloc(1000, sizeof(char));
	stream = popen(cmd, "r");
	if (stream == NULL)
	{
		printf("popen failed to execute.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		while (fgets(output + line_len, 1000, stream))
		{
			line_len += strlen(output + line_len);
		}
	}
	pclose(stream);
	return (output);
}

MU_TEST(funtion_should_expand_simple_env)
{
	char	*input; 
	char	*result; 
	char    *expected;

	printf("\n------------------------\n");
	printf(" TEST 1: expand $USER");
	printf("\n------------------------\n");

	input = ft_strdup("$USER\n");
	result = expand_token(input, 0);
	printf("expanded input: %s", result);
	expected = exec_command("echo $USER");
	mu_assert_string_eq(expected, result);
}

MU_TEST(funtion_should_expand_double_quoted_env)
{
	char	*input; 
	char	*result; 
	char    *expected;

	printf("\n------------------------\n");
	printf(" TEST 2: expand \"$USER\"");
	printf("\n------------------------\n");

	input = ft_strdup("\"$USER\"\n");
	result = expand_token(input, 0);
	printf("expanded input: %s", result);
	expected = exec_command("echo \"$USER\"");
	mu_assert_string_eq(expected, result);
}

MU_TEST(funtion_should_not_expand_single_quoted_env)
{
	char	*input; 
	char	*result; 
	char    *expected;

	printf("\n------------------------\n");
	printf(" TEST 3: not expand \'$USER\'");
	printf("\n------------------------\n");

	input = ft_strdup("\'$USER\'\n");
	result = expand_token(input, 0);
	printf("expanded input: %s", result);
	expected = exec_command("echo \'$USER\'");
	mu_assert_string_eq(expected, result);
}

MU_TEST(funtion_should_expand_quoted_cmd_simple_env)
{
	char	*input; 
	char	*result; 
	char    *expected;

	printf("\n------------------------\n");
	printf(" TEST 4: expand \"echo\" $USER");
	printf("\n------------------------\n");

	input = ft_strdup("\"echo\" $USER\n");
	result = expand_token(input, 0);
	printf("expanded input: %s", result);
	expected = exec_command("echo \"echo\" $USER");
	mu_assert_string_eq(expected, result);
}

MU_TEST(funtion_should_expand_simple_concat_str)
{
	char	*input; 
	char	*result; 
	char    *expected;

	printf("\n------------------------\n");
	printf(" TEST 5: expand echo$USER");
	printf("\n------------------------\n");

	input = ft_strdup("echo$USER\n");
	result = expand_token(input, 0);
	printf("expanded input: %s", result);
	expected = exec_command("echo echo$USER");
	mu_assert_string_eq(expected, result);
}

MU_TEST(funtion_should_expand_single_quote_concat_substr)
{
	char	*input; 
	char	*result; 
	char    *expected;

	printf("\n------------------------\n");
	printf(" TEST 6: expand 'echo'$USER'end'");
	printf("\n------------------------\n");

	input = ft_strdup("\'echo\'$USER\'end\'\n");
	result = expand_token(input, 0);
	printf("expanded input: %s", result);
	expected = exec_command("echo \'echo\'$USER\'end\'");
	mu_assert_string_eq(expected, result);
}

MU_TEST(funtion_should_expand_mult_concat_envs)
{
	char	*input; 
	char	*result; 
	char    *expected;

	printf("\n------------------------\n");
	printf(" TEST 7: expand $USER$PWD$HOME");
	printf("\n------------------------\n");

	input = ft_strdup("$USER$PWD$HOME\n");
	result = expand_token(input, 0);
	printf("expanded input: %s", result);
	expected = exec_command("echo $USER$PWD$HOME");
	mu_assert_string_eq(expected, result);
}

MU_TEST(funtion_should_expand_only_double_quoted_envs)
{
	char	*input; 
	char	*result; 
	char    *expected;

	printf("\n------------------------\n");
	printf(" TEST 8: expand \'$USER\'\"$USER\"\'$PWD\'\"$PWD\"");
	printf("\n------------------------\n");

	input = ft_strdup("\'$USER\'\"$USER\"\'$PWD\'\"$PWD\"\n");
	result = expand_token(input, 0);
	printf("expanded input: %s", result);
	expected = exec_command("echo \'$USER\'\"$USER\"\'$PWD\'\"$PWD\"");
	mu_assert_string_eq(expected, result);
}

MU_TEST(funtion_should_not_expand_double_within_single_quotes)
{
	char	*input; 
	char	*result; 
	char    *expected;

	printf("\n------------------------\n");
	printf(" TEST 9: \'\"$PWD\"\'");
	printf("\n------------------------\n");

	input = ft_strdup("\'\"$PWD\"\'\n");
	result = expand_token(input, 0);
	printf("expanded input: %s", result);
	expected = exec_command("echo \'\"$PWD\"\'");
	mu_assert_string_eq(expected, result);
}

MU_TEST(funtion_should_expand_single_within_double_quote)
{
	char	*input; 
	char	*result; 
	char    *expected;

	printf("\n------------------------\n");
	printf(" TEST 10: \"\'$PWD\'\"");
	printf("\n------------------------\n");

	input = ft_strdup("\"\'$PWD\'\"\n");
	result = expand_token(input, 0);
	printf("expanded input: %s", result);
	expected = exec_command("echo \"\'$PWD\'\"");
	mu_assert_string_eq(expected, result);
}

MU_TEST(funtion_should_expand_single_within_double_with_more_than_env)
{
	char	*input; 
	char	*result; 
	char    *expected;

	printf("\n------------------------\n");
	printf(" TEST 11: \"Hello \'start$USER\'end\"");
	printf("\n------------------------\n");

	input = ft_strdup("\"Hello \'start$USER\'end\"\n");
	result = expand_token(input, 0);
	printf("expanded input: %s", result);
	expected = exec_command("echo \"Hello \'start$USER\'end\"");
	mu_assert_string_eq(expected, result);
}

MU_TEST(funtion_should_not_expand_not_found_env)
{
	char	*input; 
	char	*result; 
	char    *expected;

	printf("\n------------------------\n");
	printf(" TEST 12: expand echo$USERend");
	printf("\n------------------------\n");

	input = ft_strdup("echo$USERend\n");
	result = expand_token(input, 0);
	printf("expanded input: %s", result);
	expected = exec_command("echo echo$USERend");
	mu_assert_string_eq(expected, result);
}

MU_TEST(funtion_should_not_expand_not_found_env_but_keep_str_end)
{
	char	*input; 
	char	*result; 
	char    *expected;

	printf("\n------------------------\n");
	printf(" TEST 13: expand echo$USR\'end\'");
	printf("\n------------------------\n");

	input = ft_strdup("echo$USR\'end\'\n");
	result = expand_token(input, 0);
	printf("expanded input: %s", result);
	expected = exec_command("echo echo$USR\'end\'");
	mu_assert_string_eq(expected, result);
}

MU_TEST(funtion_should_remove_quotes_in_middle)
{
	char	*input; 
	char	*result; 
	char    *expected;

	printf("\n------------------------\n");
	printf(" TEST 14: expand echo hello\'world\'");
	printf("\n------------------------\n");

	input = ft_strdup("echo hello\'world\'\n");
	result = expand_token(input, 0);
	printf("expanded input: %s", result);
	expected = exec_command("echo echo hello\'world\'");
	mu_assert_string_eq(expected, result);
}

MU_TEST_SUITE(test_suite)
{
	MU_RUN_TEST(funtion_should_expand_simple_env);
	MU_RUN_TEST(funtion_should_expand_double_quoted_env);
	MU_RUN_TEST(funtion_should_expand_quoted_cmd_simple_env);
	MU_RUN_TEST(funtion_should_not_expand_single_quoted_env);
	MU_RUN_TEST(funtion_should_expand_simple_concat_str);
	MU_RUN_TEST(funtion_should_expand_single_quote_concat_substr);
	MU_RUN_TEST(funtion_should_expand_mult_concat_envs);
	MU_RUN_TEST(funtion_should_expand_only_double_quoted_envs);
	MU_RUN_TEST(funtion_should_not_expand_double_within_single_quotes);
	MU_RUN_TEST(funtion_should_expand_single_within_double_quote);
	MU_RUN_TEST(funtion_should_expand_single_within_double_with_more_than_env);
	MU_RUN_TEST(funtion_should_not_expand_not_found_env);
	MU_RUN_TEST(funtion_should_not_expand_not_found_env_but_keep_str_end);
	MU_RUN_TEST(funtion_should_remove_quotes_in_middle);
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	load_environ_hashtable(envp);
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
