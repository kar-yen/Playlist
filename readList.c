// This c file is for reading song list from file or user input.
// Check if a file is specified as an argument to program.
// If so, open and read the file if it exists and readable.
// Store the list of artistes and songs in array of structure.
// If the file does not exist or is not readable, print error message and exit from the program.
// If no file is specified, the program will search for a file named "artistes+songs.txt" in current directory.
// If the file exists and readable, open and read the file.
// Then store the list of artistes and songs in array of structure.
// If the file does not exist or is not readable, print error message and prompt user to enter the information manually.
// Exit program if no input is entered.
// Store the list of artistes and songs in array of structure.

// To pass command line argument: Run -> Edit Configurations -> Enter name of text file(with .txt) in "Program Argument"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
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

int getInput(int argc, char file[]);
int specifiedFile(char file[]);
int searchDirectory();
int userInput();
int readContent(char arr[], int i, int *j);
void swapList(LIST list[], int low, int high);

int getInput(int argc, char file[]) // Function to get input
{
    int i;

    if(argc == 2) // If file is specified in command line argument
    {
        i = specifiedFile(file); // Read content of file

        return i;
    }

    else if(argc == 1) // If no file is specified
    {
        i = searchDirectory(); // Search current directory

        return i;
    }

    else // If more than one file are entered
    {
        // Print error message and exit from program
        printf("Error opening file. More than one file is specified.\n");

        exit(0);
    }
}

int specifiedFile(char file[]) // Function to read a specified file
{
    FILE *fp;
    char arr[MAX_LENGTH];
    int i = 0, j = 0;

    fp = fopen(file, "r+");

    if (fp == NULL) // Exit if error in opening file
    {
        printf("Error opening file");
        exit(0);
    } else {
        while (!feof (fp)) // Before end of file
        {
            fgets(arr, MAX_LENGTH, fp); // Store the string line by line into the array
            i = readContent(arr, i, &j); // Read content of file
        }

        fclose(fp); // Close file

        return i+1;
    }
}

int searchDirectory() // Function to search in directory
{
    FILE *fp;
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    char filename[20] = {"artistes+songs.txt"};
    char filesList[MAX_LENGTH][MAX_LENGTH];
    char arr[MAX_LENGTH];
    int flag = 0; // Variable to check if the file exists
    int i = 0, j;
    int x = 0, y = 0;

    if (d) // Search through directory
    {
        while ((dir = readdir(d)) != NULL) // Before the end of directory
        {
            strcpy(filesList[i], dir->d_name); // Copy all files name in directory into array
            i++;
        }

        closedir(d); // Close directory
    }

    for (j = 0; j < i; j++) // For loop to check if the text file exists in current directory
    {
        if (strcmp(filesList[j], filename) == 0) // If the file exists
        {
            flag = 1; // Reset flag if file exists
            fp = fopen(filename, "r+"); // Open file

            if (fp == NULL) // Prompts user to input manually if error in opening file
            {
                printf("No file found\n");
                x = userInput();

                return x;
            }
            else // Read the file
            {
                while (!feof (fp)) // Before end of file
                {
                    fgets(arr, 100, fp); // Store the string line by line into the array
                    x = readContent(arr, x, &y);
                }

                fclose(fp); // Close file

                return x + 1;
            }
        }
    }

    if(flag == 0) // If the file does not exists in the directory
    {
        // Print error message and prompt user to input manually
        printf("No file found\n");
        x = userInput();

        return x;
    }
}

int userInput() // Function for user to input manually
{
    int i = 0, j = 0;
    char tmp[MAX_LENGTH]; // Temporary array

    // Prompts user to input with specified format
    printf("Artiste name\n"
           "Song title***Song duration\n"
           "Song title***Song duration\n"
           "...\n"
           "Song title***Song duration\n"
           "<blank line>\n"
           "Artiste name\n"
           "Song title***Song duration\n"
           "Song title***Song duration\n"
           "...\n"
           "Song title***Song duration\n"
           "<blank line>\n"
           "...\n");
    printf("Please enter the artistes and songs information with the above format (max 50 artists and 50 songs per artist):\n");
    printf("Blank two lines when finish input.\n");

    memset(tmp, 0, 100); // Initialization of array
    fflush(stdin);

    do
    {
        do
        {
            i = readContent(tmp, i, &j); // Read user input
        }while(*(fgets(tmp, sizeof(tmp), stdin)) != '\n'); // If user input a blank line
        songList[i].songCount = j; // Get the number of song for each artist
        i++; // Increment of number of artist
        j = 0; // Reset the index of song title
    }while(*(fgets(tmp, sizeof(tmp), stdin)) != '\n'); // If user input another blank line

    // Error handling if input is invalid
    if(songList[0].artisteName[0] == '\0') // If user enter a blank line as first line
    {
        swapList(songList, 0, i-1); // Remove the error input
        i -= 1;
    }

    // If user enters an empty input
    if(songList[0].artisteName[0] == '\0' && songList[1].artisteName[0] == '\0')
    {
        printf("Empty input. Program exited."); // Print error message and exit from program
        exit(0);
    }

    return i;
}

int readContent(char arr[], int i, int *j) // Function to read content of the list
{
    int k;
    int point = 0;
    char *token;

    for(k = 0; k < strlen(arr); k++) // For loop tp iterate through the list
    {
        if((arr[k] == '*') && (arr[k+1] == '*') && (arr[k+2] == '*')) // If the line is a song name
        {
            point = 1; // Mark the flag if the current line is a song name
        }

        if (arr[strlen(arr) - 1] == '\n') // Convert '\n' to '\0'
        {
            arr[strlen(arr) - 1] = '\0';
        }
    }

    if(point == 0 && arr[0] != '\0') // If the current line is not a blank line and does not contain ***
    {
        strcpy(songList[i].artisteName, arr); // Read the artist name and store in the array structure
        *j = 0; // Set the index of song title as 0
    }
    else if(point == 1 && arr[0] != '\0') // If the current line is not a blank line and contains ***
    {
        token = strtok(arr, "***"); // Break the string by using ***
        strcpy(songList[i].songTitle[*j], token); // Store the first token as song title

        token = strtok(NULL, "***");
        strcpy(songList[i].songDuration[*j], token); // Store the second token as song duration
        *j += 1; // Increment of index of song title
        songList[i].songCount = *j; // Get the total song count for each artist

        point = 0; // Reset flag
    }
    if(arr[0] == '\0' && songList[i].artisteName[0] != '\0') // If the current line is a blank line
    {
        i++; // Increment of number of artist
    }
    memset(arr, 0, 100); // Reset the array by storing 0 into it

    return i;
}

void swapList(LIST list[], int low, int high) // Function to swap to artist name and their songs
{
    LIST tmp;

    tmp = list[low];
    list[low] = list[high];
    list[high] = tmp;
}