#include <stdio.h>
#include <unistd.h> // For usleep
#include <curses.h>
#include <windows.h>

int main() {
    char matriz[5][5] = {
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '}
    };

    int rotation = 0;

    while (1) {
        // Move the cursor back to the beginning
        printf("\033[H");

        // Update the matrix with the current rotation
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if ((i + rotation) % 2 == 0 && (j + rotation) % 2 == 0) {
                    matriz[i][j] = '#';
                } else {
                    matriz[i][j] = '.';
                }
            }
        }

        // Print the matrix
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                printf("%c ", matriz[i][j]);
            }
            printf("\n");
        }

        // Increase the rotation
        rotation++;

        // If we reach 2, reset to 0
        if (rotation > 1) {
            rotation = 0;
        }

        // Wait for one millisecond
        Sleep(1);
    }

    return 0;
}
