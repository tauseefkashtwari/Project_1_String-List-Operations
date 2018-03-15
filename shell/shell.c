// Shell starter file
// You may make any changes to any part of this file.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//for wait
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h> //sigactoin FOR SIGNALS
#include <ctype.h> //isdigit

#define COMMAND_LENGTH 1024
#define NUM_TOKENS (COMMAND_LENGTH / 2 + 1)
#define PATH_MAX 4096 //for comamnds
#define HISTORY_DEPTH 10 //given to us
/*#define BUFFER_SIZE 50
static char buffer[BUFFER_SIZE];*/

int count = 0; //added
//!!int numberofcommands; //added-USE 
char history[HISTORY_DEPTH][COMMAND_LENGTH] = {"",""}; //givne to us-added the ""


//DONE-100%
void add_history(char* tokens[], char* buff)
{

    int i=count;
    int j=0;
    int k=0;

    // len = sizeof(tokens[0]);
    if (strcmp(tokens[0],"")!=0)
    {
       if (strlen(tokens[0])!=0)
       {
          memset(history[i], 0, strlen(history[i]));
          for(j=0; j<COMMAND_LENGTH; j++)
          {
             if(i>9) 
             	i=i-10;
             if (tokens[0][j] == '\0')
             {
                history[i][j] = ' ';
                k++;
             }
             
             else
               history[i][j] = tokens[0][j];

            if(tokens[k] == NULL)
            {
               break;
            }

          }
       }
    }

 }


//DONE
void print_history()
{
	int i=1;

	if(count >9)
	{
		i = count-9;
	}


	char string1[i];
	char string2[sizeof(history[(i-1)%10])];


	while(i<=count)
	{

		sprintf(string1,"%d\t",i);
		write(STDOUT_FILENO,string1,strlen(string1));

		for(int j=0;j<COMMAND_LENGTH;j++)
		{
			string2[j] = history[(i-1)%10][j];
		}

		write(STDOUT_FILENO,string2,strlen(string2));
		printf("\n");
		i++;
	}
}

/**
 * Command Input and Processing
 */

/*
 * Tokenize the string in 'buff' into 'tokens'.
 * buff: Character array containing string to tokenize.
 *       Will be modified: all whitespace replaced with '\0'
 * tokens: array of pointers of size at least COMMAND_LENGTH/2 + 1.
 *       Will be modified so tokens[i] points to the i'th token
 *       in the string buff. All returned tokens will be non-empty.
 *       NOTE: pointers in tokens[] will all point into buff!
 *       Ends with a null pointer.
 * returns: number of tokens.
 */
//given-DONE
int tokenize_command(char *buff, char *tokens[])
{
	int token_count = 0;
	_Bool in_token = false;
	int num_chars = strnlen(buff, COMMAND_LENGTH);
	for (int i = 0; i < num_chars; i++) {
		switch (buff[i]) {
		// Handle token delimiters (ends):
		case ' ':
		case '\t':
		case '\n':
			buff[i] = '\0';
			in_token = false;
			break;

		// Handle other characters (may be start)
		default:
			if (!in_token) {
				tokens[token_count] = &buff[i];
				token_count++;
				in_token = true;
			}
		}
	}
	tokens[token_count] = NULL;
	return token_count;
}

/**
 * Read a command from the keyboard into the buffer 'buff' and tokenize it
 * such that 'tokens[i]' points into 'buff' to the i'th token in the command.
 * buff: Buffer allocated by the calling code. Must be at least
 *       COMMAND_LENGTH bytes long.
 * tokens[]: Array of character pointers which point into 'buff'. Must be at
 *       least NUM_TOKENS long. Will strip out up to one final '&' token.
 *       tokens will be NULL terminated (a NULL pointer indicates end of tokens).
 * in_background: pointer to a boolean variable. Set to true if user entered
 *       an & as their last token; otherwise set to false.
 */

//GIVEN-DONE
void read_command(char *buff, char *tokens[], _Bool *in_background)
{
	*in_background = false;

	// Read input
	int length = read(STDIN_FILENO, buff, COMMAND_LENGTH-1);

	//modified read command-SAT 20;50
	if ((length < 0) && (errno != EINTR)) 
	{
		perror("Unable to read command from keyboard. Terminating.\n");
		exit(-1);
	}

	// Null terminate and strip \n.
	buff[length] = '\0';
	if (buff[strlen(buff) - 1] == '\n') {
		buff[strlen(buff) - 1] = '\0';
	}

	// Tokenize (saving original command string)
	int token_count = tokenize_command(buff, tokens);
	if (token_count == 0) {
		return;
	}

	// Extract if running in background:
	if (token_count > 0 && strcmp(tokens[token_count - 1], "&") == 0) {
		*in_background = true;
		tokens[token_count - 1] = 0;
	}
}


//added
void handle_SIGINT()
{
	write(STDOUT_FILENO,"\n",strlen("\n"));
	//write(STDOUT_FILENO, buffer, strlen(buffer));
	print_history(); //UNCOMMENT THIS OUT
	//	exit(0); 
}



/**
 * Main and Execute Commands
 */
int main(int argc, char* argv[])
{
	char input_buffer[COMMAND_LENGTH];
	char *tokens[NUM_TOKENS];


	int result; //added*


	//VARIABLES FOR #4
	char *current_dir;
	char *dir;
	char *change_working_directory;
	char holder[PATH_MAX+1]; //NO POINTER*


	//signal struct
	/*sigaction structure is defined as something like:

           struct sigaction {
               void     (*sa_handler)(int);
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
           };*/


	//UNCOMMENTED OUT for 5.2

	//SIGNAL HANDLER
	/*struct sigaction handler;
	handler.sa_handler = handle_SIGINT;
	handler.sa_flags = 0;
*/

// initialise and empty a signal set.Upon successful completion, sigemptyset() returns 0. Otherwise, it returns -1 and sets errno to indicate the error.
	
	/*sigemptyset(&handler.sa_mask); 
	sigaction(SIGINT,&handler,NULL);

	strcpy(buffer,"I caught a Ctrl-C!\n");
	printf("Program now waiting for Ctrl-C.\n");*/


	while (true) 
	{

		// Get command
		current_dir = getcwd(NULL,0);


		// Use write because we need to use read() to work with
		// signals, and read() is incompatible with printf().
		write(STDOUT_FILENO,current_dir,strlen(current_dir));
		write(STDOUT_FILENO, ">", strlen(">"));
		
		_Bool in_background = false;
		read_command(input_buffer, tokens, &in_background);


		//4. INTERNAL COMMANDS


		if(tokens[0] != NULL)
		{

			//number 5
			if(strcmp(tokens[0],"!!")==0)
			{
				//DEBUGGING
				if(count == 0)
				{
					write(STDIN_FILENO,"NO PREVIOUS COMMAND\n",strlen("NO PREVIOUS COMMAND\n"));
				}

				else
				{
					//changed to <= from <
					if(history[count-1] < 0)
					{

						//display error
						write(STDIN_FILENO,"Wrong command.No previous command.\n",strlen("Wrong command.No previous command.\n"));
						write(STDIN_FILENO,"\n",strlen("\n"));
						continue;
					}


					else
					{
						//run last command
						write(STDOUT_FILENO,history[count-1],strlen(history[count-1]));
						write(STDIN_FILENO,"\n",strlen("\n"));
						tokenize_command(history[count-1],tokens);
					}
				}
			}

			//strchr - first occurrence
			//only '' instead of ""
			if(strchr(tokens[0],'!'))
			{
				int line_number = atoi(&tokens[0][1]);
				//error check- <=0 instead of <0 for that
				if(line_number > count || line_number <= 0 || line_number <count-9 || isdigit(line_number) || isalpha(line_number)) //added is alpha**
				{
					//display error
					write(STDIN_FILENO,"Wrong command",strlen("Wrong command"));	
					write(STDIN_FILENO,"\n",strlen("\n"));
					continue;
				}

				else
				{
					write(STDIN_FILENO,history[(line_number-1)%10],strlen(history[(line_number-1)%10]));
					write(STDIN_FILENO,"\n",strlen("\n"));
					tokenize_command(history[count-1],tokens);
				}
			}


			//add to hisotry if the command not there
			if(strcmp(tokens[0], "!!") !=0)
			{
				if(strcmp(tokens[0],"!n") !=0)
				{
					add_history(tokens,input_buffer);
					count++;
				}
			}



			//RETURN UPON eXIT
			if(strcmp(tokens[0],"exit")==0)
			{
				return 0;
			}

			if(strcmp(tokens[0],"pwd")==0)
			{
				change_working_directory = getcwd(holder,(PATH_MAX+1)); //buffer,size.getcwd copies an absolute pathname of cwd to the array pointed to by buf, which is of length size.				
				printf("%s\n",change_working_directory);
				continue;
			}


			if(strcmp(tokens[0],"history")==0)
			{
				print_history();
				continue;
			}
			if(strcmp(tokens[0],"cd")==0)
			{
				current_dir = (getcwd(NULL,0));
				if(tokens[1]==NULL)
				{
					continue;
				}


				if(strchr(tokens[1],'/'))
				{
					chdir(tokens[1]);
					printf("The directory has been changed to %s\n",tokens[1]);
				}

				else
				{
					dir = strcat(current_dir,"/");
					tokens[1] = strcat(dir,tokens[1]);
					chdir(tokens[1]);
				}
				continue;
			}

		}

		//Step 3: call fork()
		pid_t child = fork();

		//CHild
		if(child ==0)
		{
			if(execvp(tokens[0],tokens) <0)
			{
				//write when working with signals. Printf not work. 
				write(STDOUT_FILENO,"Error:Call to exec() failed\n",strlen("Error:Call to exec() failed\n"));
			}
			exit(-1);
		}

		//parent
		else if(child <0)
		{
			
			write(STDOUT_FILENO,"Error:call to fork() failed\n",strlen("Error:call to fork() failed\n"));
	
			
		}

		//<0
		else
		{
			//wait for process to change state
			//pid_t waitpid(pid_t pid, int *status, int options)
			waitpid(child,&result,0);
		}


//given(DONE)
		// Cleanup any previously exited background child processes
		// (The zombies)
		while (waitpid(-1, NULL, WNOHANG) > 0)
			; // do nothing.


//----------------------------------///KHATAM--------------------------------------------------------------------------------------------------
		// DEBUG: Dump out arguments:
		for (int i = 0; tokens[i] != NULL; i++) 
		{
			write(STDOUT_FILENO, "   Token: ", strlen("   Token: "));
			write(STDOUT_FILENO, tokens[i], strlen(tokens[i]));
			write(STDOUT_FILENO, "\n", strlen("\n"));
		}


		if (in_background) 
		{
			write(STDOUT_FILENO, "Run in background.", strlen("Run in background."));
		}

		/**
		 * Steps For Basic Shell:
		 * 1. Fork a child process
		 * 2. Child process invokes execvp() using results in token array.
		 * 3. If in_background is false, parent waits for
		 *    child to finish. Otherwise, parent loops back to
		 *    read_command() again immediately.
		 */

	}
	;
	return 0;
}
