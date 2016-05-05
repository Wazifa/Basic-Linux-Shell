/*
 * Name: Wazifa Jafar   
 * Description: Writing my own shell program that will accept commands
 * 		fork a child process and execute commands given by user.
 * 		The shell will keep running until user chooses to exit or
 * 		quit.
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>


int main( void )
{

	// The array input will have the data given by the user and 
	// the tokenization will be done in the same array.
	// Each word will be stored in each row of **arr.
	char input[255], **arr;
	int status;
    
    	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);

	while(1)
	{
		printf("msh> ");

		// Assuming my program will not require more than 3 parameters
		// I hardcoded an array of 4 rows.
		arr = malloc(4*sizeof(char*));
		char *temp;
		int i =-1;
        
		// temp will hold each word of the tokenization and then 
		// store in the **arr
        	fgets(input, 255, stdin);
        	temp = strtok(input, " \r\n\0");

		// If the user doesn't enter any data, the program should just 
		// go back to the beginning of the loop
		if(temp == NULL)
		{
			continue;
		}
		
		arr[i] = malloc(strlen(temp));
		arr[i] = temp;
		i++;


		//The loop will first check for quit or exit in order to exit 
		//the program.
		//Else it will check for command to change directory.
		//If it's neither of the three, it will create a child process,
		//and pass the command to execvp. 
		//Once these are done, the parent process will be killed by exit and 
		//it will loop back to the beginning.
	
		while (temp != NULL)
		{
			arr[i] = malloc(strlen(temp));
            		arr[i] = temp;
            		temp = strtok(NULL, " \r\n\0");
            		i++;
		}
		
		if (strcmp(arr[0], "exit") == 0)
        	{
            		printf("Exiting!\n");
            		exit(0);
        	}

		else if(strcmp(arr[0], "quit") == 0)
        	{
            		printf("Aborting!\n");
            		exit(0);
        	}

		else if (strcmp(arr[0], "cd") == 0)
		{
			int success;
            		success = chdir(arr[1]);
            		if(success == -1)
			{
				printf("bash: cd: %s: No such file or directory\n", arr[1]);
			}
		}

		else
		{
			pid_t pid = fork();
            		int execReturn = 0;
            		if (pid == 0)
			{
				execReturn = execvp(arr[0], arr);
                    
                    		if(execReturn == -1)
				{
					printf("%s: Command not found.\n", input);
				}
				exit(0);
			}
		}
		wait(&status);
	}
	return 0;
}
