#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

	// declares code for getLine()
	char *input = NULL;
	size_t capline = 0; // Capacity

	// declares code for strtok()
	int i;
	char *token;
	char *array[512];

	// declares startup text
	void startup(){
	printf("**************************************************************\n");
	printf("*COMMAND LINE INTERPRETER                                     \n");
	printf("*TO RUN A COMMAND SIMPLY TYPE YOUR COMMAND AND PRESS 'ENTER' *\n");
	printf("*EXAMPLE: ls -a                                              *\n");
	printf("*TO EXIT TYPE 'q'                                            *\n");
	printf("**************************************************************\n");
	}

	/* Print out "$lopes: " */
	void displayPrompt(){
		printf("$lopes: ");
	}

	/* Divide input line into tokens */
	void makeTokens(char *input){
		i = 0;
		token = strtok(input, "\n ");
			while (token != NULL) {
				array[i++] = token; // Add tokens into the array
				token = strtok(NULL, "\n ");
			}
		array[i] = NULL;
	}

	// commands are executed
   void execute(){
	   int pid = fork(); // Create a new process
				if (pid != 0) { // If not successfully completed
					int s;
					waitpid(-1, &s, 0); // Wait for process termination
			} else {
					if(execvp(array[0], array) == -1){ // If returned -1 => something went wrong! If not then command successfully completed */
                        perror("Command Not Found: "); // Display error message
                        exit(errno);
                    }
			}
   }

	int main(){
        //execute2();
		startup();
		while(1){
			displayPrompt(); // prompts the user for command input
			getline(&input, &capline, stdin); // Read the user input
			// check to see if there is any user input
				if(strcmp(input,"\n")==0){
					perror("Please type in a command " );
					continue;
				}

			makeTokens(input); // separates each term into a different token

            // exits shell on "exit" command
			if (strcmp(array[0], "exit") == 0) {
				printf("SYSTEM : exit\n");
				return 0;
			}
			execute(); // call execvp()
	}


}

