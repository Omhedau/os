
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void performSystemCalls() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("It is the child process, and pid is %d\n", getpid()); 
        execl("/bin/echo", "echo", "Hello from the child process!", (char*)0);
        perror("in exec(): ");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        printf("It is the parent process, and pid is %d\n", getpid());
        int status;
        wait(&status);
        printf("Child is reaped %d\n", status);

        if (WIFEXITED(status)) {
            printf("The process ended with exit(%d)\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("The process ended with kill-%d\n", WTERMSIG(status));
        } else {
            printf("Unknown exit status\n");
        }
    } else {
        perror("Error while forking\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    performSystemCalls();
    return 0;
}

 
