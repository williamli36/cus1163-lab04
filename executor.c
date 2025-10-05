#include "executor.h"

int execute_command(char *command, char **args) {
    pid_t pid;
    int status;

    // TODO 1: Fork a child process
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return -1;
    }

    // TODO 2: Child process - Execute the command
    if (pid == 0) {
        execvp(command, args);
        perror("execvp failed"); // only runs if execvp fails
        exit(1); // exit so child doesn't continue parent code
    }

    // TODO 3: Parent process - Wait for child to complete
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid failed");
        return -1;
    }

    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    else
        return -1;
}
