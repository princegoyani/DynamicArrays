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

#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>


// Function Declarations
void fillArray(int** mainArray, int maxWidth, int maxHeight, int values);
void printTwoDArray(int** array, int maxWidth, int maxHeight);
void printTwoDChar(char** charArray, int maxWidth, int maxHeight);
void dropDirtBall(int** mainArray, int maxWidth, int maxHeight, int power, int centerX, int centerY, int radius, int numberOfDrop);
int findMax(int** map, int maxHeight, int maxWidth);
void normalizeMap(int** map, int** newMap, int maxHeight, int maxWidth, int maxVal);
char calculateForChar(int count, int waterline);
void finalizeMap(char** charMap, int** map, int maxHeight, int maxWidth, int waterline);
void writeToIntFile(char* filename, int** array, int maxHeight, int maxWidth);
void writeToCharFile(char* filename, char** array, int maxHeight, int maxWidth);
double frand();


#endif // MAP_GENERATOR_H
