#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "executor.h"

#define MAX_INPUT 1024
#define MAX_ARGS 64

int main() {
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    char *command;
    int exit_status;

    printf("========================================\n");
    printf("   Simple Command Executor\n");
    printf("========================================\n");
    printf("Type 'exit' to quit\n\n");

    while (1) {
        printf("cmd> ");
        fflush(stdout);

        if (!fgets(input, sizeof(input), stdin)) {
            break; 
        }

        // Remove newline at end
        input[strcspn(input, "\n")] = 0;

        // Exit command
        if (strcmp(input, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }

        // Split input into args
        int i = 0;
        char *token = strtok(input, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // NULL-terminate the array

        // First token is the command
        if (i == 0) continue; // Empty input
        command = args[0];

        // Execute the command
        exit_status = execute_command(command, args);

        printf("\nCommand '%s' completed with exit status: %d\n\n", command, exit_status);
    }

    return 0;
}
