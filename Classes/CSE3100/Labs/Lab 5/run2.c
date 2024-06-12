#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char ** argv)
{
    pid_t child;
    int exitStatus;

    if (argc < 4) {
        fprintf(stderr, "Usage: %s cmd1 cmd1_arg cmd2 [cmd2_args ..]\n", argv[0]);
        return 1;
    }

    // at least, there should be 3 arguments
    char *cmd1 = argv[1];
    char *arg1 = argv[2];
    char *cmd2 = argv[3];

    child = fork();

    if(child == 0) { // child process
        execlp(cmd1, cmd1, arg1, NULL);
        perror("execlp()");
    } else {
        waitpid(child, &exitStatus, 0);
        printf("exited=%d exitstatus=%d\n", WIFEXITED(exitStatus), WEXITSTATUS(exitStatus));
        child = fork();
        if(child == 0) {
            execvp(cmd2, &argv[3]);
            perror("execlp()");
        } else {
            waitpid(child, &exitStatus, 0);
            printf("exited=%d exitstatus=%d\n", WIFEXITED(exitStatus), WEXITSTATUS(exitStatus));
        }
    }
    return 0;
}  