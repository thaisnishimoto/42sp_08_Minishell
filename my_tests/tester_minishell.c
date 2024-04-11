/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:37:32 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/11 16:19:29 by tmina-ni         ###   ########.fr       */
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

char	*exec_command(char *cmd, int exit_print)
{
	int	line_len;
	FILE	*stream;
	char	*output;

	line_len = 0;
	output = ft_calloc(2000, sizeof(char));
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
	int	exit_status = pclose(stream);
	if (exit_status == -1)
	{
		printf("pclose error\n");
		exit(EXIT_FAILURE);
	}
	if (exit_print == 1)
	        printf("EXIT CODE: %d\n", WEXITSTATUS(exit_status));
	return (output);
}

MU_TEST(function_should_run_command_echo)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 1: echo Hello");
	printf("\n------------------------\n");

	result = exec_command("echo 'echo Hello' | ./minishell", 1);
	expected = exec_command("echo Hello", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_run_command_echo_with_env)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 2: echo Hello $USER");
	printf("\n------------------------\n");

	result = exec_command("echo 'echo $USER' | ./minishell", 1);
	expected = exec_command("echo $USER", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_run_command_echo_concat_with_env)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 3: echo Hello$HOME");
	printf("\n------------------------\n");

	result = exec_command("echo 'echo Hello$HOME' | ./minishell", 1);
	expected = exec_command("echo Hello$HOME", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_run_command_echo_concat_double_quote_env)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 4: echo Hello\"$HOME\"");
	printf("\n------------------------\n");

	result = exec_command("echo \'echo Hello\"$HOME\"\' | ./minishell", 1);
	expected = exec_command("echo Hello\"$HOME\"", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_run_wrong_command)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 5: catz");
	printf("\n------------------------\n");

	result = exec_command("echo 'catz' | ./minishell", 1);
	expected = exec_command("catz", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_run_command_with_empty_env)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 6: echo $WSLENV");
	printf("\n------------------------\n");

	result = exec_command("echo 'echo $WSLENV' | ./minishell", 1);
	expected = exec_command("echo $WSLENV", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_run_command_infile_redir)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 7: < infile grep 1");
	printf("\n------------------------\n");

	result = exec_command("echo '< ./files/infile grep 1' | ./minishell", 1);
	expected = exec_command("< ./files/infile grep 1", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_try_not_found_infile_redir)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 8: < filex cat");
	printf("\n------------------------\n");

	result = exec_command("echo '< ./files/filex cat' | ./minishell", 1);
	expected = exec_command("bash -c < ./files/filex cat", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_run_multiple_infile_redirs)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 9: < infile2  <infile cat");
	printf("\n------------------------\n");

	result = exec_command("echo '< ./files/infile2 <./files/infile cat' | ./minishell", 1);
	expected = exec_command("bash -c < ./files/infile2 <./files/infile cat", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_run_multiple_infile_redirs_first_not_found)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 10: < infilex  <infile cat");
	printf("\n------------------------\n");

	result = exec_command("echo '< ./files/infilex <./files/infile cat' | ./minishell", 1);
	expected = exec_command("bash -c < ./files/infilex <./files/infile cat", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_run_multiple_infile_redirs_last_not_found)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 11: < infile < infilex grep 1");
	printf("\n------------------------\n");

	result = exec_command("echo '< ./files/infile <./files/infilex grep 1' | ./minishell", 1);
	expected = exec_command("bash -c < ./files/infile <./files/infilex grep 1", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_run_command_new_outfile_redir)
{
	char    *expected = "Files ./files/outfile1 and ./files/outfile1_expected are identical\n";
	char	*diff_result;
	char    *outfile;

	printf("\n------------------------\n");
	printf(" TEST 12: echo New oufile test > outfile1");
	printf("\n------------------------\n");

	exec_command("echo 'echo New outfile teste > ./files/outfile1' | ./minishell", 1);
	exec_command("echo New outfile teste > ./files/outfile1_expected", 1);

	diff_result = exec_command("diff -s ./files/outfile1 ./files/outfile1_expected", 0);
	outfile = exec_command("cat ./files/outfile1", 0);
	ft_printf("Outfile: %s", outfile);
	mu_assert_string_eq(expected, diff_result);
	free(diff_result);
	free(outfile);
}

MU_TEST(function_should_run_command_trunc_outfile_redir)
{
	char    *expected = "Files ./files/outfile1 and ./files/outfile1_expected are identical\n";
	char	*diff_result;
	char    *outfile;

	printf("\n------------------------\n");
	printf(" TEST 13: echo Old oufile teste! > outfile1");
	printf("\n------------------------\n");

	exec_command("echo 'echo Truncate! > ./files/outfile1' | ./minishell", 1);
	exec_command("echo Truncate! > ./files/outfile1_expected", 1);

	diff_result = exec_command("diff -s ./files/outfile1 ./files/outfile1_expected", 0);
	outfile = exec_command("cat ./files/outfile1", 0);
	ft_printf("Outfile: %s", outfile);
	mu_assert_string_eq(expected, diff_result);
	free(diff_result);
	free(outfile);
}

MU_TEST(function_should_run_command_append_outfile_redir)
{
	char    *expected = "Files ./files/outfile1 and ./files/outfile1_expected are identical\n";
	char	*diff_result;
	char    *outfile;

	printf("\n------------------------\n");
	printf(" TEST 14: echo Append text!! >>outfile1");
	printf("\n------------------------\n");

	exec_command("echo 'echo Append text!! >>./files/outfile1' | ./minishell", 1);
	exec_command("echo Append text!! >>./files/outfile1_expected", 1);

	diff_result = exec_command("diff -s ./files/outfile1 ./files/outfile1_expected", 0);
	outfile = exec_command("cat ./files/outfile1", 0);
	ft_printf("Outfile: %s", outfile);
	mu_assert_string_eq(expected, diff_result);
	free(diff_result);
	free(outfile);
}

MU_TEST(function_should_run_command_multiple_outfile_redir)
{
	char    *expected2 = "Files ./files/outfile2 and ./files/outfile2_expected are identical\n";
	char    *expected3 = "Files ./files/outfile3 and ./files/outfile3_expected are identical\n";
	char	*diff_result;
	char    *outfile;

	printf("\n------------------------\n");
	printf(" TEST 15: echo oi > outfile2 > outfile3");
	printf("\n------------------------\n");

	exec_command("echo 'echo oi > ./files/outfile2 >./files/outfile3' | ./minishell", 1);
	exec_command("echo oi > ./files/outfile2_expected >./files/outfile3_expected", 1);

	diff_result = exec_command("diff -s ./files/outfile2 ./files/outfile2_expected", 0);
	outfile = exec_command("cat ./files/outfile2", 0);
	ft_printf("Outfile: %s", outfile);
	mu_assert_string_eq(expected2, diff_result);
	free(diff_result);
	free(outfile);

	diff_result = exec_command("diff -s ./files/outfile3 ./files/outfile3_expected", 0);
	outfile = exec_command("cat ./files/outfile3", 0);
	ft_printf("Outfile: %s", outfile);
	mu_assert_string_eq(expected3, diff_result);
	free(diff_result);
	free(outfile);
}

MU_TEST(funtion_should_run_two_heredocs)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 16: << EOF << EOF1");
	printf("\n------------------------\n");

	result = exec_command("< ./files/test_multiple_hdoc.txt ./minishell", 1);
	expected = exec_command("bash -c cat << EOF << EOF1\nHello\nEOF1\nEOF\nBye\nEOF\nEOF1\n", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(funtion_should_run_heredoc_expanding_vars)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 17: cat << EOF multiple ENV");
	printf("\n------------------------\n");

	result = exec_command("< ./files/test_hdoc_vars.txt ./minishell", 1);
	expected = exec_command("bash -c cat << EOF\n\"$USER\"\n'$USER'\n$USR\n$\"USER\"\n$'USER'\n\"'$USER'\"\n'\"$USER\"'\n$USERoi\noi$USER\n$\n$?\nEOF\n", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_run_pipeline_ls_l_wc_l)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 18: ls -l | wc -l");
	printf("\n------------------------\n");

	result = exec_command("echo 'ls -l | wc -l' | ./minishell", 1);
	expected = exec_command("ls -l | wc -l", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_run_pipeline_echo_hello_grep_without_arg)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 19: echo hello | grep");
	printf("\n------------------------\n");

	result = exec_command("echo 'echo hello | grep' | ./minishell", 1);
	expected = exec_command("echo hello | grep", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_run_pipeline_first_invalid)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 20: echoo hello | echo bye");
	printf("\n------------------------\n");

	result = exec_command("echo 'echoo hello | echo bye' | ./minishell", 1);
	expected = exec_command("echoo hello | echo bye", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_run_pipeline_second_invalid)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 21: echo hello | echoo bye");
	printf("\n------------------------\n");

	result = exec_command("echo 'echo hello | echoo bye' | ./minishell", 1);
	expected = exec_command("echo hello | echoo bye", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_run_multiple_pipeline)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 22: echo hello | rev | rev");
	printf("\n------------------------\n");

	result = exec_command("echo 'echo hello | rev | rev' | ./minishell", 1);
	expected = exec_command("echo hello | rev | rev", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_run_pipeline_in_redir)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 23: < infile grep Hello | wc -w");
	printf("\n------------------------\n");

	result = exec_command("echo '< ./files/infile2 grep Hello | wc -w' | ./minishell", 1);
	expected = exec_command("< ./files/infile2 grep Hello | wc -w", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_run_pipeline_in_out_redir)
{
	char    *expected4 = "Files ./files/outfile4 and ./files/outfile4_expected are identical\n";
	char    *expected5 = "Files ./files/outfile5 and ./files/outfile5_expected are identical\n";
	char	*diff_result;
	char    *outfile;

	printf("\n------------------------\n");
	printf(" TEST 24: < infile cat | grep 1 > outfile4 >> outfile5");
	printf("\n------------------------\n");

	exec_command("echo '< ./files/infile cat | grep 1  > ./files/outfile4 >>./files/outfile5' | ./minishell", 1);
	exec_command("< ./files/infile cat | grep 1  > ./files/outfile4_expected >>./files/outfile5_expected", 1);

	diff_result = exec_command("diff -s ./files/outfile4 ./files/outfile4_expected", 0);
	outfile = exec_command("cat ./files/outfile4", 0);
	ft_printf("Outfile4: %s", outfile);
	mu_assert_string_eq(expected4, diff_result);
	free(diff_result);
	free(outfile);

	diff_result = exec_command("diff -s ./files/outfile5 ./files/outfile5_expected", 0);
	outfile = exec_command("cat ./files/outfile5", 0);
	ft_printf("Outfile5: %s", outfile);
	mu_assert_string_eq(expected5, diff_result);
	free(diff_result);
	free(outfile);
}

MU_TEST(function_should_run_pipeline_invalid_in_echo_out)
{
	char    *expected4 = "Files ./files/outfile4 and ./files/outfile4_expected are identical\n";
	char	*diff_result;
	char    *outfile;

	printf("\n------------------------\n");
	printf(" TEST 25: < infilex cat | echo hello > outfile4");
	printf("\n------------------------\n");

	exec_command("echo '< infilex cat | echo hello  > ./files/outfile4' | ./minishell", 1);
	exec_command("< infilex cat | echo hello  > ./files/outfile4_expected", 1);

	diff_result = exec_command("diff -s ./files/outfile4 ./files/outfile4_expected", 0);
	outfile = exec_command("cat ./files/outfile4", 0);
	ft_printf("Outfile4: %s", outfile);
	mu_assert_string_eq(expected4, diff_result);
	free(diff_result);
	free(outfile);
}

MU_TEST(function_should_run_out_redir_mid_pipeline)
{
	char	*result;
	char	*expected;
	char    *expected4 = "Files ./files/outfile4 and ./files/outfile4_expected are identical\n";
	char    *expected5 = "Files ./files/outfile5 and ./files/outfile5_expected are identical\n";
	char	*diff_result;
	char    *outfile;

	printf("\n------------------------\n");
	printf(" TEST 26: echo oi > outfile4 | rev > outfile5 | < infile cat");
	printf("\n------------------------\n");

	result = exec_command("echo ' echo oi > ./files/outfile4 | rev  > ./files/outfile5 | < ./files/infile cat' | ./minishell", 1);
	expected = exec_command("echo oi > ./files/outfile4_expected | rev > ./files/outfile5_expected | < ./files/infile cat", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);

	diff_result = exec_command("diff -s ./files/outfile4 ./files/outfile4_expected", 0);
	outfile = exec_command("cat ./files/outfile4", 0);
	ft_printf("Outfile 4: %s", outfile);
	mu_assert_string_eq(expected4, diff_result);
	free(diff_result);
	free(outfile);

	diff_result = exec_command("diff -s ./files/outfile5 ./files/outfile5_expected", 0);
	outfile = exec_command("cat ./files/outfile5", 0);
	ft_printf("Outfile 5: %s", outfile);
	mu_assert_string_eq(expected5, diff_result);
	free(diff_result);
	free(outfile);
}

MU_TEST(funtion_should_run_command_echo_tr_with_invalid_infile)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 27: < invalid_file echo oi | echo bye");
	printf("\n------------------------\n");

	result = exec_command("echo '< invalid_file echo oi | echo bye' | ./minishell", 1);
	expected = exec_command("< invalid_file echo oi | echo bye", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(funtion_should_run_heredocs_with_pipe_and_exit_code)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 28: << EOF cat | << EOF1 cat");
	printf("\n------------------------\n");

	result = exec_command("< ./files/test_hdoc_pipeline.txt ./minishell", 1);
	expected = exec_command("bash -c cat << EOF << EOF1\n$?\nEOF\n$?\nEOF1\n", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(function_should_run_redir_pipeline_without_cmd)
{
	char	*result;
	char	*expected;
	char    *expected4 = "Files ./files/outfile4 and ./files/outfile4_expected are identical\n";
	char    *expected5 = "Files ./files/outfile5 and ./files/outfile5_expected are identical\n";
	char	*diff_result;
	char    *outfile;

	printf("\n------------------------\n");
	printf(" TEST 29: << EOF > outfile4 | << EOF2 > outfile5");
	printf("\n------------------------\n");

	result = exec_command("< ./files/test_hdoc_pipe_no_cmd.txt ./minishell", 1);
	expected = exec_command("bash -c << EOF > ./files/outfile4_expected | << EOF1 > ./files/outfile5_expected\n$?\nEOF\n$?\nEOF1\n", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);

	diff_result = exec_command("diff -s ./files/outfile4 ./files/outfile4_expected", 0);
	outfile = exec_command("cat ./files/outfile4", 0);
	ft_printf("Outfile 4: %s", outfile);
	mu_assert_string_eq(expected4, diff_result);
	free(diff_result);
	free(outfile);

	diff_result = exec_command("diff -s ./files/outfile5 ./files/outfile5_expected", 0);
	outfile = exec_command("cat ./files/outfile5", 0);
	ft_printf("Outfile 5: %s", outfile);
	mu_assert_string_eq(expected5, diff_result);
	free(diff_result);
	free(outfile);
}

MU_TEST(funtion_should_run_heredoc_single_quote_eof_not_expanding_vars)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 30: cat << ' EOF ' cat");
	printf("\n------------------------\n");

	result = exec_command("< ./files/test_hdoc_vars_single_quote.txt ./minishell", 1);
	expected = exec_command("bash -c cat << ' EOF '\n\"$USER\"\n'$USER'\n$USR\n$\"USER\"\n$'USER'\n\"'$USER'\"\n'\"$USER\"'\n$USERoi\noi$USER\n$\n$?\n' EOF '\n EOF \n", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

MU_TEST(funtion_should_run_heredoc_double_quote_eof_not_expanding_vars)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 31: cat << \"E O F\" cat");
	printf("\n------------------------\n");

	result = exec_command("< ./files/test_hdoc_vars_double_quote.txt ./minishell", 1);
	expected = exec_command("bash -c cat << \"E O F\"\n\"$USER\"\n'$USER'\n$USR\n$\"USER\"\n$'USER'\n\"'$USER'\"\n'\"$USER\"'\n$USERoi\noi$USER\n$\n$?\n\"E O F\"\nE O F\n", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

//MU_TEST(funtion_should_create_outfile_and_run_2nd_command)
//{
//	char    *expected = "Files ../outfile6 and ../outfile_expected6 are identical\n";
//	char    *outfile;
//	char    *diff_result;
//
//	printf("\n------------------------\n");
//	printf(" TEST 6: invalid infile");
//	printf("\n------------------------\n");
//
//	exec_command("< file_x cat | ls > ../outfile_expected6");
//	exec_command("../pipex_bonus file_x \"cat\" \"ls\" ../outfile6");
//
//	diff_result = exec_command("diff -s ../outfile6 ../outfile_expected6");
//	ft_printf("%s", diff_result);
//	outfile = exec_command("cat ../outfile6");
//	ft_printf("Pipex outfile: %s\n", outfile);
//	mu_assert_string_eq(expected, diff_result);
//	free(diff_result);
//}
//
//MU_TEST(funtion_should_run_command_echo_tr_space)
//{
//	char    *expected = "Files ../outfile7 and ../outfile_expected7 are identical\n";
//	char    *outfile;
//	char    *diff_result;
//
//	printf("\n------------------------\n");
//	printf(" TEST 7: echo | tr space");
//	printf("\n------------------------\n");
//
//	exec_command("< infile echo \"h e l l o\" | tr -d ' ' > ../outfile_expected7");
//	exec_command("../pipex_bonus infile \"echo \'h e l l o\'\" \"tr -d ' '\" ../outfile7");
//
//	diff_result = exec_command("diff -s ../outfile7 ../outfile_expected7");
//	ft_printf("%s", diff_result);
//	outfile = exec_command("cat ../outfile7");
//	ft_printf("Pipex outfile: %s\n", outfile);
//	mu_assert_string_eq(expected, diff_result);
//	free(diff_result);
//}
//
//MU_TEST(funtion_should_try_run_command_without_x_permission)
//{
//	char    *expected = "Files ../outfile8 and ../outfile_expected8 are identical\n";
//	char    *outfile;
//	char    *diff_result;
//
//	printf("\n------------------------\n");
//	printf(" TEST 8: cmd not executable");
//	printf("\n------------------------\n");
//
//	exec_command("< infile grep pipex | /dev/null > ../outfile_expected8");
//	exec_command("../pipex_bonus infile \"grep pipex\" \"/dev/null\" ../outfile8");
//
//	diff_result = exec_command("diff -s ../outfile8 ../outfile_expected8");
//	ft_printf("%s", diff_result);
//	outfile = exec_command("cat ../outfile8");
//	ft_printf("Pipex outfile: %s\n", outfile);
//	mu_assert_string_eq(expected, diff_result);
//	free(diff_result);
//}
//
//MU_TEST(funtion_should_try_run_command_with_path)
//{
//	char    *expected = "Files ../outfile9 and ../outfile_expected9 are identical\n";
//	char    *outfile;
//	char    *diff_result;
//
//	printf("\n------------------------\n");
//	printf(" TEST 9: 1st command with path");
//	printf("\n------------------------\n");
//
//	exec_command("< infile ///////usr/bin/grep 1 | wc -l > ../outfile_expected9");
//	exec_command("../pipex_bonus infile \"///////usr/bin/grep 1\" \"wc -l\" ../outfile9");
//
//	diff_result = exec_command("diff -s ../outfile9 ../outfile_expected9");
//	ft_printf("%s", diff_result);
//	outfile = exec_command("cat ../outfile9");
//	ft_printf("Pipex outfile: %s\n", outfile);
//	mu_assert_string_eq(expected, diff_result);
//	free(diff_result);
//}
//
//MU_TEST(funtion_should_run_5_commands)
//{
//	char    *expected = "Files ../outfile10 and ../outfile_expected10 are identical\n";
//	char    *outfile;
//	char    *diff_result;
//
//	printf("\n------------------------\n");
//	printf(" TEST 10 - BONUS: 5 cmds");
//	printf("\n------------------------\n");
//
//	exec_command("< infile2 cat | head -n 5 | grep x | tr -d ' ' | rev > ../outfile_expected10");
//	exec_command("../pipex_bonus infile2 \"cat\" \"head -n 5\" \"grep x\" \"tr -d ' '\" \"rev\" ../outfile10");
//
//	diff_result = exec_command("diff -s ../outfile10 ../outfile_expected10");
//	ft_printf("%s", diff_result);
//	outfile = exec_command("cat ../outfile10");
//	ft_printf("Outfile: %s", outfile);
//	mu_assert_string_eq(expected, diff_result);
//	free(diff_result);
//}
//
//MU_TEST(funtion_should_overwrite_output)
//{
//	char    *expected = "Files ../outfile10 and ../outfile_expected10 are identical\n";
//	char    *outfile;
//	char    *diff_result;
//
//	printf("\n------------------------\n");
//	printf(" TEST 10.2 - BONUS: overwrite output");
//	printf("\n------------------------\n");
//
//	exec_command("< infile2 cat | head -n 5 | grep x | tr -d ' ' | rev > ../outfile_expected10");
//	exec_command("../pipex_bonus infile2 \"cat\" \"head -n 5\" \"grep x\" \"tr -d ' '\" \"rev\" ../outfile10");
//
//	diff_result = exec_command("diff -s ../outfile10 ../outfile_expected10");
//	ft_printf("%s", diff_result);
//	outfile = exec_command("cat ../outfile10");
//	ft_printf("Outfile: %s", outfile);
//	mu_assert_string_eq(expected, diff_result);
//	free(diff_result);
//}
//
//MU_TEST(funtion_should_run_here_doc)
//{
//	char    *expected = "Files ../outfile11 and ../outfile_expected11 are identical\n";
//	char    *outfile;
//	char    *diff_result;
//
//	printf("\n------------------------\n");
//	printf(" TEST 11 - BONUS: here_doc input: Hello World!");
//	printf("\n------------------------\n");
//
//	exec_command("cat << EOF | rev >> ../outfile_expected11\nHello World!\nEOF\n");
//	exec_command("../pipex_bonus here_doc EOF \"cat\" \"rev\" ../outfile11");
//
//	diff_result = exec_command("diff -s ../outfile11 ../outfile_expected11");
//	ft_printf("%s", diff_result);
//	outfile = exec_command("cat ../outfile11");
//	ft_printf("Outfile: %s", outfile);
//	mu_assert_string_eq(expected, diff_result);
//	free(diff_result);
//}
//
//MU_TEST(funtion_should_append_output)
//{
//	char    *expected = "Files ../outfile11 and ../outfile_expected11 are identical\n";
//	char    *outfile;
//	char    *diff_result;
//
//	printf("\n------------------------\n");
//	printf(" TEST 11.2 - BONUS: append HELLO! to output");
//	printf("\n------------------------\n");
//
//	exec_command("cat << EOF | rev >> ../outfile_expected11\nHELLO!\nEOF\n");
//	exec_command("../pipex_bonus here_doc EOF \"cat\" \"rev\" ../outfile11");
//
//	diff_result = exec_command("diff -s ../outfile11 ../outfile_expected11");
//	ft_printf("%s", diff_result);
//	outfile = exec_command("cat ../outfile11");
//	ft_printf("Outfile: %s", outfile);
//	mu_assert_string_eq(expected, diff_result);
//	free(diff_result);
//}

MU_TEST_SUITE(test_suite)
{
	MU_RUN_TEST(function_should_run_command_echo);
	MU_RUN_TEST(function_should_run_command_echo_with_env);
	MU_RUN_TEST(function_should_run_command_echo_concat_with_env);
	MU_RUN_TEST(function_should_run_command_echo_concat_double_quote_env);
	MU_RUN_TEST(function_should_run_wrong_command);
	MU_RUN_TEST(function_should_run_command_with_empty_env);
	MU_RUN_TEST(function_should_run_command_infile_redir);
	MU_RUN_TEST(function_should_try_not_found_infile_redir);
	MU_RUN_TEST(function_should_run_multiple_infile_redirs);
	MU_RUN_TEST(function_should_run_multiple_infile_redirs_first_not_found);
	MU_RUN_TEST(function_should_run_multiple_infile_redirs_last_not_found);
	MU_RUN_TEST(function_should_run_command_new_outfile_redir);
	MU_RUN_TEST(function_should_run_command_trunc_outfile_redir);
	MU_RUN_TEST(function_should_run_command_append_outfile_redir);
	MU_RUN_TEST(function_should_run_command_multiple_outfile_redir);
	MU_RUN_TEST(funtion_should_run_two_heredocs);
	MU_RUN_TEST(funtion_should_run_heredoc_expanding_vars);
	MU_RUN_TEST(function_should_run_pipeline_ls_l_wc_l);
	MU_RUN_TEST(function_should_run_pipeline_echo_hello_grep_without_arg);
	MU_RUN_TEST(function_should_run_pipeline_first_invalid);
	MU_RUN_TEST(function_should_run_pipeline_second_invalid);
	MU_RUN_TEST(function_should_run_multiple_pipeline);
	MU_RUN_TEST(function_should_run_pipeline_in_redir);
	MU_RUN_TEST(function_should_run_pipeline_in_out_redir);
	MU_RUN_TEST(function_should_run_pipeline_invalid_in_echo_out);
	MU_RUN_TEST(function_should_run_out_redir_mid_pipeline);
	MU_RUN_TEST(funtion_should_run_command_echo_tr_with_invalid_infile);
	MU_RUN_TEST(funtion_should_run_heredocs_with_pipe_and_exit_code);
	MU_RUN_TEST(function_should_run_redir_pipeline_without_cmd);
	MU_RUN_TEST(funtion_should_run_heredoc_single_quote_eof_not_expanding_vars);
	MU_RUN_TEST(funtion_should_run_heredoc_double_quote_eof_not_expanding_vars);
//	MU_RUN_TEST(funtion_should_run_command_ls_l_wc_l);
//	MU_RUN_TEST(funtion_should_run_command_grep_a1_wc_w);
//	MU_RUN_TEST(funtion_should_run_command_cat_ls_l);
//	MU_RUN_TEST(funtion_should_run_command_cat_wc);
//	MU_RUN_TEST(funtion_should_run_command_echo_tr);
//	MU_RUN_TEST(funtion_should_create_outfile_and_run_2nd_command);
//	MU_RUN_TEST(funtion_should_run_command_echo_tr_space);
//	MU_RUN_TEST(funtion_should_try_run_command_without_x_permission);
//	MU_RUN_TEST(funtion_should_try_run_command_with_path);
//	MU_RUN_TEST(funtion_should_run_5_commands);
//	MU_RUN_TEST(funtion_should_overwrite_output);
//	MU_RUN_TEST(funtion_should_run_here_doc);
//	MU_RUN_TEST(funtion_should_append_output);
//hdoc and redir middle of pipeline
//$? expansion in middle of pipeline
//cat | cat | ls
}

int	main(void)
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
