#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

#define BUFFER_SIZE 80

int is_palindrome(char *str) {
    int l = 0;
    int h = strlen(str) - 1;
    while (h > l) {
        if (str[l++] != str[h--]) {
            return 0;
        }
    }
    return 1;
}

int count_vowels(char *str) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = tolower(str[i]);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            count++;
        }
    }
    return count;
}

int main() {
    int pipe1[2];
    int pipe2[2];
    char input_str[BUFFER_SIZE];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    pid_t p2 = fork();

    if (p2 < 0) {
        perror("First fork failed");
        return 1;
    }

    if (p2 > 0) {
        // --- Process P1 ---
        // P1 only writes to pipe1
        close(pipe1[0]);
        close(pipe2[0]);
        close(pipe2[1]);

        printf("[P1] Enter a string (max 80 chars): ");
        if (fgets(input_str, BUFFER_SIZE, stdin) != NULL) {
            // Remove trailing newline character
            input_str[strcspn(input_str, "\n")] = '\0';
        }

        write(pipe1[1], input_str, strlen(input_str) + 1);
        close(pipe1[1]);

        wait(NULL); // Wait for child to finish
    } else {
        // Inside P2 fork context
        pid_t p3 = fork();

        if (p3 < 0) {
            perror("Second fork failed");
            return 1;
        }

        if (p3 > 0) {
            // --- Process P2 ---
            // P2 reads from pipe1 and writes to pipe2
            close(pipe1[1]);
            close(pipe2[0]);

            char buffer[BUFFER_SIZE];
            read(pipe1[0], buffer, BUFFER_SIZE);
            close(pipe1[0]);

            printf("[P2] Received string: \"%s\"\n", buffer);
            printf("[P2] Number of vowels: %d\n", count_vowels(buffer));

            write(pipe2[1], buffer, strlen(buffer) + 1);
            close(pipe2[1]);

            wait(NULL); // Wait for P3 to finish
            exit(0);
        } else {
            // --- Process P3 ---
            // P3 only reads from pipe2
            close(pipe1[0]);
            close(pipe1[1]);
            close(pipe2[1]);

            char buffer[BUFFER_SIZE];
            read(pipe2[0], buffer, BUFFER_SIZE);
            close(pipe2[0]);

            printf("[P3] Received string: \"%s\"\n", buffer);
            if (is_palindrome(buffer)) {
                printf("[P3] Result: The string IS a palindrome.\n");
            } else {
                printf("[P3] Result: The string IS NOT a palindrome.\n");
            }
            exit(0);
        }
    }

    return 0;
}
