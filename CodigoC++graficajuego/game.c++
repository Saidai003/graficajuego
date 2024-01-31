#include <stdio.h>
#include <unistd.h> // For usleep
#include <curses.h>

int main() {
    initscr(); // Initialize the window
    noecho(); // Don't echo() while we do getch
    cbreak(); // Disable line buffering 

    char world[5][5] = {
        {'o', 'o', 'T', 'o', 'o'},
        {'o', 'o', 'o', 'o', 'o'},
        {'T', 'o', 'o', 'T', 'o'},
        {'o', 'o', 'o', 'o', 'T'},
        {'o', 'T', 'o', 'o', 'o'}
    };

    int playerX = 1;
    int playerY = 1;

    while (1) {
        // Move the cursor back to the beginning
        printf("\033[H");

        // Print the world
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (i == playerY && j == playerX) {
                    printf("@ ");
                } else {
                    printf("%c ", world[i][j]);
                }
            }
            printf("\n");
        }

        // Get the player's input
        int input = getch();

        // Update the player's position based on the input
        if (input == 'w' && playerY > 0) {
            playerY--;
        } else if (input == 'a' && playerX > 0) {
            playerX--;
        } else if (input == 's' && playerY < 4) {
            playerY++;
        } else if (input == 'd' && playerX < 4) {
            playerX++;
        }

        // Wait for one millisecond
        usleep(100000);
    }

    endwin(); // End curses mode

    return 0;
}
