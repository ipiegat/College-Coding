#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <fcntl.h>
#include <sys/stat.h>

//redirect standard input to the specified file
void redirectStdin(const char *filename)
{
        int fd = open(filename, O_RDONLY);
        if(fd < 0)
        {
                perror("Error opening the file\n");
                exit(-1);
        }
	//TODO
        if(dup2(fd, 0) == -1) 
        {
                perror("Redirecting error");
                exit(-1);
        }
        close(fd);
        //fill in the code below

}

//redirect standad output to the specified file
void redirectStdout(const char *filename)
{
        int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if(fd < 0)
        {
                perror("Error opening the file\n");
                exit(-1);
        }
	//TODO
	//fill in the code below
        if(dup2(fd, 1) == -1) 
        {
                perror("Redirecting error");
                exit(-1);
        }
        close(fd);

}

//TODO: imeplement the following function
//if word has letters in strict alphabetical order, return 1 else return 0
int increasing(char *word)
{
        if(strlen(word)<5) return 0;
        //TODO
        int len = strlen(word);

        for (int i = 0; i < len - 1; i++) {
                if (word[i] >= word[i + 1]) {
            return 0;
        }
    }
    return 1; 
}

