
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


int execlp(const char *file, const char *arg, ...);
int execvp(const char *file, char * const argv[]);

pid_t wait(int *stat_loc);
pid_t waitpid(pid_t, int *stat_loc, int options);

int parseLine(char *arg, char **input);

int main (int argc, char *argv[])
{

	// infinite loop 

	while(1)
	{
		char line[50];		//command line input
		char *input[50];
		char *exitString = "exit"; 
		int amp = 0;
		

		//prompt
		printf("# -> ");

		//get command line input
		gets(line);	

		//parse command input
		amp = parseLine(line,input);	

		
		//exit the shell if input is "exit"
		if(strcmp(input[0], exitString) == 0)		
		{
			printf("Exiting shell program. \n");
			exit(0);
		}
		
	
		int procid;
		procid = fork();

		if (procid == 0)
		{
			//child processing here
			//if amp == 1, command executes concurrently with the shell 

			execvp(input[0],input);

	
			if(execvp(input[0], input) < 0)				
			{
				printf(" ERROR: execvp failed \n");
				exit(1);
			}
		
		}

		else if(amp == 0)	
		{
			//parent processing here
			//wait until terminated child process status obtained 

			wait(&procid); 		

		}

	}

	return 0;

}


int parseLine(char *arg, char **input)
{

	int ampersand = 0;

	//while reading command input
	while(*arg)
	{

		//add null terminator after each individual argument 
		while( *arg == ' ' || *arg == '\n')
		{
			*arg ++= '\0';
		}

		*input++=arg;
		
		//look for more arguments 
		while(*arg != '\0' && *arg != ' ' && *arg != '\n')
		{
			arg++;

			//check for '&' --> commands with '&' should run concurrent with shell
			if(*arg == '&')
			{
				ampersand = 1;
				*arg = '\0';
			}
		}
	}
	
	*input = NULL;
	return ampersand;

}

	


