#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../include/pipe.h"

void demonstrate_ls_grep_pipe(void)
{
    int fd[2];
    pid_t ls_pid;
    pid_t grep_pid;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return;
    }

    printf("\n=== ls -l | grep \".c\" Demo ===\n");

    /* First child: ls -l */
    ls_pid = fork();

    if (ls_pid == -1)
    {
        perror("fork");
        return;
    }

    if (ls_pid == 0)
    {
        close(fd[0]);

        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

execlp("ls", "ls", "-l", "src", NULL);
        perror("execlp ls");
        exit(EXIT_FAILURE);
    }

    /* Second child: grep ".c" */
    grep_pid = fork();

    if (grep_pid == -1)
    {
        perror("fork");
        return;
    }

    if (grep_pid == 0)
    {
        close(fd[1]);

        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

execlp("grep", "grep", "\\.c$", NULL);

        perror("execlp grep");
        exit(EXIT_FAILURE);
    }

    /* Parent */
    close(fd[0]);
    close(fd[1]);

    waitpid(ls_pid, NULL, 0);
    waitpid(grep_pid, NULL, 0);

    printf("=== Pipe demonstration completed ===\n");
}
