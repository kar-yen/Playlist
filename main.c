// Main.c file of the program
// Array of structures is used.
// 6 .c files including main.c and 5 .h files are contained in this program.
// 5 different test files are located in current directory.

#include "readList.h" // Header file to read the list
#include "sortList.h" // Header file to sort the list
#include "printList.h" // Header file to print sorted list
#include "randomizedList.h" // Header file for randomised playlist
#include "outputFile.h" // Header file to create output file
#define MAX_LENGTH 100

typedef struct{
    char artisteName[MAX_LENGTH]; // Array to store artist name
    char songTitle[MAX_LENGTH][MAX_LENGTH]; // 2D string array to store song title
    char songDuration[MAX_LENGTH][6]; // Array to store song duration in type char
    int songDurationInSecs[MAX_LENGTH]; // Array to store the converted song duration in type int
    int songCount; // Number of songs for each artist
    int counter; // Counter to count the number of songs in randomised playlist
}LIST;

LIST songList[MAX_LENGTH]; // Array of structure to store the song list

int main(int argc, char* argv[]) // Read file from command line argument
{
    int artistCount; // Number of artist in the song list

    artistCount = getInput(argc, argv[1]); // Get song list from file or user

    sortMain(artistCount); // Sort the song list by alphabetical order

    createFile(artistCount); // Create a new file and write sorted list in the file

    print(artistCount); // Print the sorted song list

    randomisedPlaylistMain(artistCount); // Print the randomised playlist

    return 0;
}