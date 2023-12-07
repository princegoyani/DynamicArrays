/*
Name: Prince Shaileshbhai Goyani
Date: 11/12/2023
Description: This program generates a 2D simulated landmass using procedural generation. It allows for terrain customization through parameters like size, waterline, and terrain features. The output includes a character-based map representation of the terrain, suitable for uses in simulations or game development.
Usage:
"Compile: Compile the code using a C compiler, e.g., gcc terrain_gen.c -o terrain_gen -lm.
Run: Execute with ./terrain_gen for random terrain or ./terrain_gen <seed> for a specific seed.
Input Parameters: Enter values for terrain dimensions, waterline, and other features as prompted.
Output: The terrain is printed to the console and saved in text files (raw_landmass.txt, normalized_landmass.txt, final_landmass.txt)."
*/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "goyani_prince_hw4.h"

// Function to fill a 2D array with a given value.
void fillArray(int** mainArray, int maxWidth, int maxHeight, int values){
    // Loop through each element and set it to 'values'.
    for (int i = 0; i < maxHeight; i++){
        for (int j = 0; j < maxWidth; j++){
            mainArray[i][j] = values;
        }
    }
}

// Function to print a 2D integer array.
void printTwoDArray(int** array, int maxWidth, int maxHeight){ 
    for (int i = 0; i < maxHeight; i++){
        for (int j = 0; j < maxWidth; j++){
            // Format the output based on the value size for alignment.
            int element = array[i][j];
                printf("%4d", element);
            }
        printf("\n");
    }
}

// Function to print a 2D character array.
void printTwoDChar(char** charArray, int maxWidth, int maxHeight){ 
    for (int i = 0; i < maxHeight; i++){
        for (int j = 0; j < maxWidth; j++){
            printf("%c", charArray[i][j]);
        }
        printf("\n");
    }
}

// Function to check if a given point is within specified bounds.
bool boundCheck(int x, int y, int minx, int miny, int maxx, int maxy){
    return (minx <= x) && (miny <= y) && (x < maxx) && (y < maxy);
}

// Function to simulate dropping of dirt balls on a map.
void dropDirtBall(int** mainArray, int maxWidth, int maxHeight, int power, int centerX, int centerY, int radius, int numberOfDrop){
    for (int k = 0; k < numberOfDrop; k++){
        centerX = floor(frand() * maxWidth);
        centerY = floor(frand() * maxHeight);

        for (int i = centerY - radius; i <= centerY + radius; i++){
            for (int j = centerX - radius; j <= centerX + radius; j++){
                if(!boundCheck(i, j, 0, 0, maxHeight, maxWidth)) continue;

                float distance = sqrt(pow((i - centerY), 2) + pow((j - centerX), 2));
                if (distance > radius) continue;       

                int impValue = power - floor(distance);
                mainArray[i][j] += impValue;
            }
        }
    }
}

// Function to find the maximum value in a 2D array.
int findMax(int** map, int maxHeight, int maxWidth){
    int maxValue = 0;
    for (int i = 0; i < maxHeight; i++){
        for (int j = 0; j < maxWidth; j++){
            int tempElement = map[i][j];
            if (maxValue < tempElement){
                maxValue = tempElement;
            }
        }
    }
    return maxValue;
}

// Function to normalize values in a map based on the maximum value.
void normalizeMap(int** map, int** newMap, int maxHeight, int maxWidth, int maxVal){
    for (int i = 0; i < maxHeight; i++){
        for (int j = 0; j < maxWidth; j++){
            float tempElement = map[i][j];
            float dividedVal = tempElement / maxVal;
            newMap[i][j] = (int)(dividedVal * 255);
        }
        free(map[i]);
    }
}

// Function to convert integer values to characters based on thresholds.
char calculateForChar(int count, int waterline){
    int landzone = 255 - waterline;
    if (count < floor(.5 * waterline)) return '#';
    if ((count >= floor(.5 * waterline)) && (count <= waterline)) return '~';
    if(count > waterline){
        if (count < floor(waterline + (0.15 * landzone))) return '.';
        if ((count >= floor(waterline + (0.15 * landzone))) && (count < floor(waterline + (0.40 * landzone)))) return '-';
        if ((count >= floor(waterline + (0.40 * landzone))) && (count < floor(waterline + (0.80 * landzone)))) return '*';
        return '^';
    }
    return '?';
}

// Function to finalize the map by converting integers to characters.
void finalizeMap(char** charMap, int** map, int maxHeight, int maxWidth, int waterline){
    for (int i = 0; i < maxHeight; i++){
        for (int j = 0; j < maxWidth; j++){
            charMap[i][j] = calculateForChar(map[i][j], waterline);
        }
        free(map[i]);
    }
}

// Function to write a 2D integer array to a file.
void writeToIntFile(char *filename, int** array, int maxHeight, int maxWidth){
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < maxHeight; i++){
        for (int j = 0; j < maxWidth; j++){
            fprintf(file, "%4d", array[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

// Function to write a 2D character array to a file.
void writeToCharFile(char *filename, char** array, int maxHeight, int maxWidth){
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < maxHeight; i++){
        for (int j = 0; j < maxWidth; j++){
            fprintf(file, "%c", array[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

// Function to generate a random double.
double frand(){
    return (double)rand() / ((double)RAND_MAX+1);
}

// Main function to run the program.
int main(int argc, char *argv[]){
    // Seed the random number generator.
    if (argc == 3){
        char *a = argv[2];
        int integerTime = atoi(a);
        srand(integerTime);  
    } else {
        srand(time(0));  
    }

    // Prompt user for input parameters.
    printf("Welcome to Prince’s CSE240 Terraformer!!");
    int width, height, waterline, radius, power, numberOfDrop;


    int shouldBeGood = 0;

    while (shouldBeGood <= 3){
    printf("\nEnter grid width:");
    scanf("%d", &width);
    printf("\nEnter grid height:");
    scanf("%d", &height);
    printf("\nEnter value for waterline (40-200):");
    scanf("%d", &waterline);
    printf("\nEnter dirtball radius (minimum 2):");
    scanf("%d", &radius);
    printf("\nEnter dirtball power rating (minimum = radius):");
    scanf("%d", &power);
    printf("\nEnter number of dirtballs to drop:");
    scanf("%d", &numberOfDrop);

    if ( width>=0 && height>=0 && waterline>=40 && waterline<=200 && radius>=2 && power >= radius && numberOfDrop>0){
        shouldBeGood=1;
        break;
    }

    printf("\nThere is Some Error in provided inputs\n");
    printf("Please Try Again (Try:1/3)\n");
    shouldBeGood++;
    }

    // Initialize and allocate arrays.
    int** mainArray = (int**)malloc(height * sizeof(int*));
    int** secondArray = (int**)malloc(height * sizeof(int*));
    for (int i = 0; i < height; i++){
        mainArray[i] = (int*)malloc(width * sizeof(int));
        secondArray[i] = (int*)malloc(width * sizeof(int));
    }

    printf("\n");
    // Process and print map.
    fillArray(mainArray, width, height, 0);
    dropDirtBall(mainArray, width, height, power, width/2, height/2, radius, numberOfDrop);
    printTwoDArray(mainArray, width, height);
    writeToIntFile("raw_landmass.txt", mainArray, height, width);
    printf("\n\n");

    int maxValue = findMax(mainArray, height, width);
    normalizeMap(mainArray, secondArray, height, width, maxValue);
    free(mainArray);
    printTwoDArray(secondArray, width, height);
    writeToIntFile("normalized_landmass.txt", secondArray, height, width);

    printf("\n\n");
    // Convert to character map and free memory.
    char** charArray = (char**)malloc(height * sizeof(char*));
    for (int i = 0; i < height; i++){    
        charArray[i] = (char*)malloc(width * sizeof(char));
    }
    finalizeMap(charArray, secondArray, height, width, waterline);
    free(secondArray);
    printTwoDChar(charArray, width, height);
    writeToCharFile("final_landmass.txt", charArray, height, width);

    for (int i = 0; i < height; i++){
        free(charArray[i]);
    }
    free(charArray);

    return 0;
}
