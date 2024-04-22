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

[About the project](https://github.com/thaisnishimoto/42sp_08_Minishell?tab=readme-ov-file#mandatory-part)

[Functionality](https://github.com/thaisnishimoto/42sp_08_Minishell?tab=readme-ov-file#my-tester)

[Usage](https://github.com/thaisnishimoto/42sp_08_Minishell?tab=readme-ov-file#my-tester)

<h2>
About the Project
</h2>

<h2>
Functionality
</h2>

`Minishell` has Bash as a reference. It supports the following features: <be>
* Prompt display
* Command history (up and down arrows)
* Syntax verification
* Command search and execution (using a relative or an absolute path)
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
  * `>` redirects output in truncate mode
  * `>>` redirects output in append mode
  * `<` redirects input
  * `<< DELIMITER` opens a heredoc, reads user input until seeing a line containing the `DELIMITER`, and is a way to redirect multi-line input to a command. (it does not update command history)
* Environment variables (i.e. `$USER` or `$VAR`) and token expansions.
  * `$` - followed by a variable name, expands to the environment variable`s value
  * `$?` expands to the exit status of the most recently executed command
  * `~` expands to $HOME variable value
  * `#` - it and all subsequent characters up to the next <newline> are discarded as a comment
  * `Single quotes` prevent interpretation of metacharacters (i.e. echo `$USER` will literally print `$USER`).
  * `Double quotes` prevent interpretation of metacharacters but allow variable expansion (i.e. echo `"< $USER"` will print `<` followed by the value of `$USER`).
  * When a heredoc delimiter is a variable, it is not expanded
  * When a heredoc delimiter is quoted, variables in the input are not expanded
  * When expanded, a variable can be executed (i.e. export `a="echo hello"`, `$a` will execute echo and print hello)
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

<h2>
Usage
</h2>

Clone the repository:
```sh
git clone git@github.com:thaisnishimoto/42sp_08_Minishell.git
```
Compile:
```sh
make
```
To check for memory leaks using valgrind, suppressing the readline library leaks: 
```sh
make leak
```
Run program:
```
./minishell
```
End program:
```
exit
```
