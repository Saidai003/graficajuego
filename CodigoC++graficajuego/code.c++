#include <stdio.h>
#include <unistd.h> // For usleep

int main() {
    char matriz[5][5] = {
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '}
    };

    char caracter = 'A';

    while (1) {
        // Move the cursor back to the beginning
        printf("\033[H");
        
        // Update the matrix with the current character
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                matriz[i][j] = caracter;
            }
        }

        // Print the matrix
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                printf("%c ", matriz[i][j]);
            }
            printf("\n");
        }

        // Increase the character by one
        caracter++;

        // If we reach 'Z', reset to 'A'
        if (caracter > 'Z') {
            caracter = 'A';
        }

        // Wait for one millisecond
        usleep(100000);
    }

    return 0;
}