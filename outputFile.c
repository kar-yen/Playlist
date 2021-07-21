// This c file is to create a new file with content of sorted list.

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

void createFile(int artistCount) // Function to create a new file and write sorted list in it
{
    FILE *fp = fopen("SortedList.txt", "w"); // Create a new file named SortedList.txt in current directory
    if(fp == NULL)
    {
        printf("Unable to create file for sorted list.\n"); // Print error message if fail to create file
    }
    else
    {
        // Write the sorted list in new file
        for(size_t i = 0; i < artistCount; i++)
        {
            fprintf(fp, "%s\n", songList[i].artisteName);
            for (size_t j = 0; j < songList[i].songCount; j++) // Loop until j reach the number of song for each artist
            {
                // Write the song title and the respective song duration according the format in the file
                fprintf(fp, "  o %s***", songList[i].songTitle[j]);
                fprintf(fp, "%s\n", songList[i].songDuration[j]);
            }
            fprintf(fp, "\n");
        }
        fclose(fp); // Close file
    }
}