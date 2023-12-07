
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Function prototypes
void initializeArray(int **array, int width, int height);
void dropDirtballs(int **array, int width, int height, int water_line, int radius, int power_rating, int num_dirtballs);
void displayArray(int **array, int width, int height, int water_line);
int getIntegerInput(const char *prompt);

int main() {
    // Initialize random seed
    srand(time(NULL));

    int width = getIntegerInput("Enter the width of the land: ");
    int height = getIntegerInput("Enter the height of the land: ");
    int water_line = getIntegerInput("Enter the water-line value (between 40 and 200): ");
    int radius = getIntegerInput("Enter the radius of the dirtballs: ");
    int power_rating = getIntegerInput("Enter the power rating of the dirtballs: ");
    int num_dirtballs = getIntegerInput("Enter the number of dirtballs to drop: ");

    // Create and initialize the 2D array
    int **array = (int **)malloc(height * sizeof(int *));
    for (int i = 0; i < height; i++) {
        array[i] = (int *)malloc(width * sizeof(int));
    }
    initializeArray(array, width, height);

    // Drop the dirtballs
    dropDirtballs(array, width, height, water_line, radius, power_rating, num_dirtballs);

    // Display the array
    displayArray(array, width, height, water_line);

    // Free the dynamically allocated memory
    for (int i = 0; i < height; i++) {
        free(array[i]);
    }
    free(array);

    return 0;
}

// Initializes the 2D array with zeros
void initializeArray(int **array, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            array[i][j] = 0;
        }
    }
}

// Drops dirtballs onto the array
void dropDirtballs(int **array, int width, int height, int water_line, int radius, int power_rating, int num_dirtballs) {
    for (int d = 0; d < num_dirtballs; d++) {
        // Pick a random center point for the dirtball
        int centerX = rand() % width;
        int centerY = rand() % height;

        // Calculate the effect of the dirtball on the extended Moore neighborhood
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int distance = (int)floor(sqrt(pow(i - centerY, 2) + pow(j - centerX, 2)));
                if (distance <= radius) {
                    array[i][j] += power_rating - distance;
                }
            }
        }
    }
}

// Displays the array using numbers
void displayArray(int **array, int width, int height, int water_line) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (array[i][j] < water_line) {
                printf("%2d ", 0); // Water represented by 0
            } else {
                printf("%2d ", array[i][j]); // Land height represented by its value
            }
        }
        printf("\n");
    }
}

// Helper function to get integer input from the user
int getIntegerInput(const char *prompt) {
    int input;
    printf("%s", prompt);
    scanf("%d", &input);
    return input;
}
