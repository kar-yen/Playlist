// This c file is for printing the sorted list of artistes and songs.
// Print the sorted list by specified format.

#include <stdio.h>
#define MAX_LENGTH 100

typedef struct{
    char artisteName[MAX_LENGTH];
    char songTitle[MAX_LENGTH][MAX_LENGTH];
    char songDuration[MAX_LENGTH][6];
    int songDurationInSecs[MAX_LENGTH];
    int songCount;
    int counter;
}LIST;

LIST songList[MAX_LENGTH];

void print(int artistCount) // Function to print the sorted song list
{
    int i, j;

    printf("Sorted song list:\n");

    for (i = 0; i < artistCount; i++) // Before the end of list
    {
        printf("%s\n", songList[i].artisteName); // Print artist name
        for (j = 0; j < songList[i].songCount; j++) // Loop until j reach the number of song for each artist
        {
            // Print the song title and the respective song duration according the format
            printf("  o %s***", songList[i].songTitle[j]);
            printf("%s\n", songList[i].songDuration[j]);
        }
        printf("\n");
    }
}