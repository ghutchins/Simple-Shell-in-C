NAME:  Georgina Hutchins
CSC-241 - Lab3


The C program lab3_Hutchins.c is a simple shell program. Once executed, the program will output an additional user prompt, and wait for a command. The shell prompt is "# -> ". The program then parses the input and creates a child process to execute the command using execvp(). If the command has the '&' operator as the command terminator, then that command will be executed concurrently with the shell.

If the command line input is "exit," then the shell program will terminate. 


Program compiled using gcc -Wall -o executable lab3_Hutchins.c