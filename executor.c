#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * Execute a command using the fork-exec-wait pattern.
 *
 * 1. Fork a child process
 * 2. Child executes the target command via execvp()
 * 3. Parent waits for the child and returns its exit status
 */
int execute_command(char *command, char **args) {
    pid_t pid;
    int status;

    /* TODO 1: Fork a child process */
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return -1; // Fork error
    }

    /* TODO 2: Child process - Execute the command */
    if (pid == 0) {
        execvp(command, args); // Replace process image
        perror("execvp");      // Only runs if execvp fails
        exit(1);               // Must exit, not return
    }

    /* TODO 3: Parent process - Wait for child to complete */
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid failed");
        return -1;
    }

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status); // Normal exit → return exit code
    } else {
        return -1; // Abnormal termination
    }
}
