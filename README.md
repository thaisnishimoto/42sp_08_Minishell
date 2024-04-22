<p align="center">
  <img src="https://github.com/thaisnishimoto/42-project-badges/blob/main/badges/minishellm.png" alt="Minishell bonus"/>
</p>

<h1 align=center>
	<b>Minishell</b>
</h1>

<p align="center"><i>"This project is about creating a simple shell. Yes, your own little bash. You will learn a lot about processes and file descriptors."</i></p>  

<h2>
 Status
</h2>

**Finished:**  2024, April 13th <br>
**Grade:** 101/100

<h2>
Content
</h2>

[Mandatory Part](https://github.com/thaisnishimoto/42sp_07_PushSwap#about-the-project---mandatory-part)

[My Tester](https://github.com/thaisnishimoto/42sp_07_PushSwap#my-tester)

<h2>
Mandatory Part
</h2>

### Functionality
`Minishell` has Bash as a reference. It supports the following features: <be>
* Prompt display
* Command history (up and down arrows)
* Syntax verification
* Token expansions
  *
  * `#` - it and all subsequent characters up to, but excluding, the next <newline> if discarded as a comment
* Execute commands (using a relative or an absolute path)
* Builtin commands:
  * `echo` (with option `-n`)
  * `cd` (with only a relative or absolute path)
  * `pwd` (no options)
  * `export` (no options)
  * `unset` (no options)
  * `env` (no options or arguments)
  * `exit` (no options) 
* Pipes `|` which redirect output from one command to input for the next
* Redirections:
  * `>` redirects output in truncate
  * `>>` redirects output in append mode
  * `<` redirects input
  * `<< DELIMITER` opens a heredoc, reads user input until seeing a line containing the `DELIMITER`, redirects the input to command input (does not update history)
* Environment variables (i.e. `$USER` or `$VAR`) that expand to their values.
  * `$?` expands to the exit status of the most recently executed foreground pipeline.
  * When a heredoc delimiter is 
* Signals in interactive mode:
  * `ctrl-c` displays a new prompt line
  * `ctrl-d` exits minishell
  * `ctrl-\` does nothing
* Signals in exec mode:
  * `ctrl-c` displays a new prompt line
  * `ctrl-d` sends an end-of-file to the command
  * `ctrl-\` quits
* Signals inside a heredoc:
  * `ctrl-c` closes heredoc
  * `ctrl-d` closes heredoc with a warning
  * `ctrl-\` does nothing

### Usage example

```sh
git clone git@github.com:thaisnishimoto/42sp_07_PushSwap.git
```
```sh
make
```
```
$>./push_swap 25 -19 42 -7 0
pb
pb
ra
pa
rra
pa
ra
ra

$>ARG="25 -19 42 -7 0"; ./push_swap $ARG | wc -l
8
```

### Usage example

```sh
make bonus
```
```
$>./checker 3 1 2
ra
[ctrl + d]
OK

$>./checker 3 1 2
sa
[ctrl + d]
KO

$>ARG="25 -19 42 -7 0"; ./push_swap $ARG | ./checker $ARG
OK
```

<br>
<h2>
My Tester
</h2>

I wrote a script to run multiple tests on `push_swap`. <br>
It has 2 arguments:
* Amount of tests - it runs this amount of tests and shows the count of operations needed for each of them.
* Amount of numbers - it generates this amount of random numbers for each test. 
At the end, it checks if the sorting was done correctly (OK/KO) and displays the average of moves among all the tests run.

### Usage

Copy [my_test directory](https://github.com/thaisnishimoto/42sp_07_PushSwap/tree/master/my_tests) into your project's directory.
```sh
cp push_swap ./my_tests/push_swap
```
```sh
cd my_tests
```
```sh
cp push_swap ./my_tests/push_swap
```
```sh
chmod +x checker_linux push_swap
```
```sh
bash tester_push.sh [amout of tests] [amount of numbers]
```

### Example
```
$> bash tester_push.sh 10 100
--------------------------------------------------
      PUSH SWAP TESTER: Sorting 100 numbers
--------------------------------------------------

Test 1. [OK] (550 moves) 
Test 2. [OK] (603 moves) 
Test 3. [OK] (576 moves) 
Test 4. [OK] (585 moves) 
Test 5. [OK] (598 moves) 
Test 6. [OK] (570 moves) 
Test 7. [OK] (606 moves) 
Test 8. [OK] (571 moves) 
Test 9. [OK] (632 moves) 
Test 10. [OK] (637 moves) 

----Results----
OK: [10/10]
Avg moves:592
```
