This was the most challenging project in the 42 vienna cursus that I have done 
so far. It was also the first project that had to be done in groups of 2.
In the end I can say that I now have a broader understanding on how the 
bash works, even though I feel like I have only scratched the surface.

About the project:

The minishell is a program that imitates the behaviour of the bash. Most
commands are launched via the executables, only the builtins echo, cd, pwd, 
export, unset, env and exit were designed by ourselves.

Redirections and pipes work as intended. It also handles closed single and 
double quotes and treats an unclosed single or double quote like an escaped
sign. Other special characters like semicolon or backslash were not required
by subject, thus not implemented.

Environment variables get expanded like in bash. 

The minishell can handle the signals ctrl-C and ctrl-\ like the bash. Also 
ctrl-D behaves like in bash.
