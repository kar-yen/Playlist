// This c file is for producing and printing randomised playlist.
// Convert the string array contains song duration into integer by converting minutes seconds into seconds.
// Produce a randomised playlist which has a total duration as close as possible to 1 hour == 60minutes == 3600 seconds.
// A modified Fisher and Yates' original algorithm(Pencil and paper method) is used to generate random permutation.
// The program strike out the selected number by swapping the chosen song to the last position in the current array.
// Then, the total number of songs for the artist is decrement after swapping. So the same song will not appear twice in the playlist.
// Link to check Fisher and Yates' original algorithm: https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle#Pencil-and-paper_method
// The program will check if any artist already has 3 songs in the playlist or no more songs available during the process of producing randomised playlist.
// If so, move the artist and songs to the last position in array of structures and decrement the number of artist available.
// Besides, if an artist has more than two songs in a row, the program will choose another song from different artist.
// Songs played after the 55 minutes will be checked to ensure the total duration of the playlist is close to 1 hour. (Below or above 60 minutes)
// Finally, the program will print out the playlist by following the specified format and the total duration of the playlist.

// Extra: The program can create an output file which has randomised playlist as contents.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "readList.h"
#include "sortList.h"
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
const char fName[] = {"RandomisedPlaylist.txt"};

void randomisedPlaylistMain(int count);
void charToInt(int count);
int randomise(int count, int flag);
void checkSong(int *count, int *total);
int pickSong(int total, int *randNum);
void swap(LIST list[], int low, int high);
int ifTriplePlay(char str[], int total, int randNum);
void printPlaylist(char str[], int j, int *counter, int *duration, int index, int flag);
void printSong(int *duration, int i, int j, int flag);
void printDuration(int duration, int flag);

void randomisedPlaylistMain(int count) // Main function to produce and print the randomised playlist
{
    int duration;
    int flag = 0; // Variable to check if file is created
    FILE *fp = fopen(fName, "w");
    if(fp == NULL)
    {
        flag = 1; // Mark if file cannot be created
        printf("Unable to create file for randomised playlist.\n");
    }

    charToInt(count); // Convert duration from minutes second to second

    printf("Randomised playlist\n");

    if(flag == 0) // If file is created successfully
    {
        // Write the string into the file
        fprintf(fp, "%s", "Randomised playlist\n");
    }

    fclose(fp); // Close file

    duration = randomise(count, flag); // Print playlist and get total duration of randomised playlist

    printDuration(duration, flag); // Print the total duration

}

void charToInt(int count) // Function to convert the song duration from string into numbers
{
    char tmp[6];
    int second;
    int minToSec;

    for(size_t i = 0; i < count; i++)
    {
        for(size_t j = 0; j < songList[i].songCount; j++)
        {
            strcpy(tmp, songList[i].songDuration[j]); // Copy the string into a temporary array

            if(tmp[1] == ':') // If song duration less than 10 minutes
            {
                second = ((tmp[2] - '0') * 10) + (tmp[3] - '0'); // Calculate the seconds
                minToSec = (tmp[0] - '0') * 60; // Convert minutes into seconds
                songList[i].songDurationInSecs[j] = minToSec + second; // Sum and store the duration in seconds
            }
            else if(tmp[2] == ':') // If song duration more than 10 minutes
            {
                second = ((tmp[3] - '0') * 10) + (tmp[4] - '0'); // Calculate seconds
                minToSec = (((tmp[0] - '0') * 10) + (tmp[1] - '0')) * 60; // Convert minutes into seconds
                songList[i].songDurationInSecs[j] = minToSec + second; // Sum and store the duration in seconds
            }
        }
    }
}

int randomise(int count, int flag) // Function to produce a randomised playlist
{
    char str[50]; // Array to memorise the artist name of previous song in randomised playlist
    int j, randNum, total, index;
    int counter = 1; // Variable which acts as a counter to help to prevent triple play
    int duration = 0;
    int tmp;

    srand(time(0)); // Use current time as seed for random number generator

    while(duration < 3600) // While loop to start last song on or before 59:59
    {
        total = 0; // Initialise total number of songs available
        checkSong(&count, &total); // Check if any artist does not meet requirements

        if(count == 0) // Exit from the loop if there is no more songs available
        {
            break;
        }

        j = pickSong(total, &randNum); // Pick a random song from the list

        // If an artist has more than two songs in a row
        if(counter == 2 && strcmp(str, songList[j].artisteName) == 0)
        {
            if(count == 1) // If no more songs available or last artist left
            {
                break;
            }
            else
            {
                j = ifTriplePlay(str, total, randNum); // Pick another random song from different artist
            }
        }

        index = randNum + songList[j].songCount; // Calculate the index of songs for the chosen artist

        if(duration >= 3300) // If loop to control the total duration of playlist as close as possible to 1 hour
        {
            tmp = duration + songList[j].songDurationInSecs[index];
            // Check if total duration is closer to one hour if current song is added into playlist
            if((3600 - duration) < abs(3600 - tmp))
            {
                break;
            }
        }

        printPlaylist(str, j, &counter, &duration, index, flag); // Print the chosen random songs
    }

    return duration;
}

void checkSong(int *count, int *total) // Function to check if an artist has more than 3 songs
{
    for(size_t i = 0; i < *count; i++)
    {
        // Check if an artist has more than 3 songs or no more songs available
        if(songList[i].counter >= 3 || songList[i].songCount == 0)
        {
            swap(songList, i, *count-1); // Swap the current artist to the last position
            *count -= 1; // Reduce number of artist by 1
        }
        if(i != *count) // If index i is not equal to the number of artist
        {
            *total += songList[i].songCount; // Sum the number of songs of all available artist
        }
    }
}

int pickSong(int total, int *randNum) // Function to pick a random song from the song list
{
    int j = 0;

    *randNum = rand() % total; // Get a random number in range from 0 to total number of songs
    while(*randNum >= 0) // Find the song from the list
    {
        *randNum = *randNum - songList[j].songCount;
        j++; // Increment of index of artist
    }

    return j - 1;
}

void swap(LIST list[], int low, int high) // Function to swap artist and their songs
{
    LIST tmp;

    tmp = list[low];
    list[low] = list[high];
    list[high] = tmp;
}

int ifTriplePlay(char str[], int total, int randNum) // Function to handle triple play
{
    int i = 0;

    randNum = rand() % total; // Generate a random number in range from 0 to total number of songs
    while(randNum >= 0) // Get the position of artist and song in structure array
    {
        randNum = randNum - songList[i].songCount;
        i++;
    }

    if(strcmp(str, songList[i-1].artisteName) == 0) // If the selected song is from the same artist
    {
        ifTriplePlay(str, total, randNum); // Call the function recursively until another song from different artist is selected
    }

    return i - 1;
}

// Function to print randomised playlist
void printPlaylist(char str[], int j, int *counter, int *duration, int index, int flag)
{
    if(strcmp(str, songList[j].artisteName) == 0) // If the artist of current song is same from the last song
    {
        *counter += 1; // Increment of counter
        printSong(duration, j, index, flag); // Print the information of selected song
    }
    else // If the artist of current song is different from the last song
    {
        *counter = 1; // Reset the counter
        strcpy(str, songList[j].artisteName); // Copy the artist name to compare with the next song
        printSong(duration, j, index, flag); // Print the information of selected song
    }
}

void printSong(int *duration, int i, int j, int flag) // Function to print the artist name, song title and song duration
{
    FILE *fp = fopen(fName, "a"); // Append the content of file instead of overwriting it

    *duration += songList[i].songDurationInSecs[j]; // Add the duration of current song into total duration of playlist
    // Print the playlist with specified format
    printf("%s: \"%s\" (%s)\n", songList[i].artisteName, songList[i].songTitle[j], songList[i].songDuration[j]);
    if(flag == 0) // If file created successfully
    {
        // Write the content in the file
        fprintf(fp, "%s: \"%s\" (%s)\n", songList[i].artisteName, songList[i].songTitle[j], songList[i].songDuration[j]);
    }
    swapSong(songList[i].songTitle, songList[i].songDuration, j, songList[i].songCount-1); // Swap the selected song to the last position of the array
    songList[i].songCount--; // Decrease the number of songs of the current artist
    songList[i].counter++; // Increase the counter of the current artist


    fclose(fp); // Close file
}

void printDuration(int duration, int flag) // Function to print the total duration of playlist
{
    int sec, min;
    FILE *fp = fopen(fName, "a"); // Append the content of file instead of overwriting it

    // Convert second to minute second
    sec = duration % 60;
    min = (duration - sec) / 60;

    if(sec < 10) // If second is single digit
    {
        printf("\nTotal duration: %d:0%d.\n", min, sec); // Print the total duration
        if(flag == 0) // If file created successfully
        {
            fprintf(fp, "\nTotal duration: %d:0%d.\n", min, sec); // Write the duration in file
        }
    }
    else // If second is two digits
    {
        printf("\nTotal duration: %d:%d.\n", min, sec); // Print the total duration
        if(flag == 0) // If file created successfully
        {
            fprintf(fp, "\nTotal duration: %d:%d.\n", min, sec); // Write the duration in file
        }
    }

    fclose(fp); // Close file
}