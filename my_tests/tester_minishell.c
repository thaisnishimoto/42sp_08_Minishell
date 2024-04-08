/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:37:32 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/08 15:38:15 by tmina-ni         ###   ########.fr       */
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

MU_TEST(funtion_should_run_heredoc_expanding_var)
{
	char	*result;
	char	*expected;

	printf("\n------------------------\n");
	printf(" TEST 16: cat << EOF Hello World!");
	printf("\n------------------------\n");

	result = exec_command("< test_hdoc_input.txt ./minishell", 1);
	expected = exec_command("bash -c cat << EOF\n\"$USER\"\n'$USER'\n$USR\n$\"USER\"\n$'USER'\n\"'$USER'\"\n'\"$USER\"'\n$USERoi\noi$USER\n$\n$?\nEOF\n", 1);
	printf("%s", result);
	mu_assert_string_eq(expected, result);
	free(result);
	free(expected);
}

//MU_TEST(function_should_run_command_ls_l_wc_l)
//{
//	char    *expected = "Files ../outfile and ../outfile_expected are identical\n";
//	char    *outfile;
//	char    *diff_result;
//
//	printf("\n------------------------\n");
//	printf(" TEST 1: ls -l | wc -l");
//	printf("\n------------------------\n");
//
//	exec_command("< infile ls -l | wc -l > ../outfile_expected");
//	exec_command("../pipex_bonus infile \"ls -l\" \"wc -l\" ../outfile");
//
//	diff_result = exec_command("diff -s ../outfile ../outfile_expected");
//	ft_printf("%s", diff_result);
//	outfile = exec_command("cat ../outfile");
//	ft_printf("Outfile: %s", outfile);
//	mu_assert_string_eq(expected, diff_result);
//	free(diff_result);
//}
//
//
//MU_TEST(funtion_should_run_command_grep_a1_wc_w)
//{
//	char    *expected = "Files ../outfile2 and ../outfile_expected2 are identical\n";
//	char    *outfile;
//	char    *diff_result;
//
//	printf("\n------------------------\n");
//	printf(" TEST 2: grep a1 | wc -w");
//	printf("\n------------------------\n");
//
//	exec_command("< infile grep a1 | wc -w > ../outfile_expected2");
//	exec_command("../pipex_bonus infile \"grep a1\" \"wc -w\" ../outfile2");
//
//	diff_result = exec_command("diff -s ../outfile2 ../outfile_expected2");
//	ft_printf("%s", diff_result);
//	outfile = exec_command("cat ../outfile2");
//	ft_printf("Outfile: %s", outfile);
//	mu_assert_string_eq(expected, diff_result);
//	free(diff_result);
//}
//
//MU_TEST(funtion_should_run_command_cat_ls_l)
//{
//	char    *expected = "Files ../outfile3 and ../outfile_expected3 are identical\n";
//	char    *outfile;
//	char    *diff_result;
//
//	printf("\n------------------------\n");
//	printf(" TEST 3: cat | ls -l");
//	printf("\n------------------------\n");
//
//	exec_command("< infile cat | ls -l > ../outfile_expected3");
//	exec_command("../pipex_bonus infile \"cat\" \"ls -l\" ../outfile3");
//
//	diff_result = exec_command("diff -s ../outfile3 ../outfile_expected3");
//	ft_printf("%s", diff_result);
//	outfile = exec_command("cat ../outfile3");
//	ft_printf("Outfile: %s", outfile);
//	mu_assert_string_eq(expected, diff_result);
//	free(diff_result);
//}
//
//MU_TEST(funtion_should_run_command_cat_wc)
//{
//	char    *expected = "Files ../outfile4 and ../outfile_expected4 are identical\n";
//	char    *outfile;
//	char    *diff_result;
//
//	printf("\n------------------------\n");
//	printf(" TEST 4: cat | wc");
//	printf("\n------------------------\n");
//
//	exec_command("< infile cat | wc > ../outfile_expected4");
//	exec_command("../pipex_bonus infile \"cat\" \"wc\" ../outfile4");
//
//	diff_result = exec_command("diff -s ../outfile4 ../outfile_expected4");
//	ft_printf("%s", diff_result);
//	outfile = exec_command("cat ../outfile4");
//	ft_printf("Outfile: %s", outfile);
//	mu_assert_string_eq(expected, diff_result);
//	free(diff_result);
//}
//
//MU_TEST(funtion_should_run_command_echo_tr)
//{
//	char    *expected = "Files ../outfile5 and ../outfile_expected5 are identical\n";
//	char    *outfile;
//	char    *diff_result;
//
//	printf("\n------------------------\n");
//	printf(" TEST 5: echo | tr -d");
//	printf("\n------------------------\n");
//
//	exec_command("< infile echo h_e_l_l_o_ _w_o_r_l_d | tr -d _ > ../outfile_expected5");
//	exec_command("../pipex_bonus infile \"echo h_e_l_l_o_ _w_o_r_l_d\" \"tr -d _\" ../outfile5");
//
//	diff_result = exec_command("diff -s ../outfile5 ../outfile_expected5");
//	ft_printf("%s", diff_result);
//	outfile = exec_command("cat ../outfile5");
//	ft_printf("Outfile: %s", outfile);
//	mu_assert_string_eq(expected, diff_result);
//	free(diff_result);
//}
//
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
	MU_RUN_TEST(funtion_should_run_heredoc_expanding_var);
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
}

int	main(void)
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
