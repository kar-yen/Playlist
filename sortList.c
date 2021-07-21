// This c file is for sorting the list of artistes and songs.
// Use quick sort algorithm and median of three algorithm to sort the list by artistes name.
// After that, sort the songs for each artist by using quick sort algorithm and median of three algorithm.

#include <stdio.h>
#include <string.h>
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

void sortMain(int num);
void quickSortArtist(LIST list[], int low, int high);
int partitionArtist(LIST list[], int low, int high);
void swapArtist(LIST list[], int low, int high);
void quickSortSong(char song[][MAX_LENGTH], char time[][6], int low, int high);
int partitionSong(char song[][MAX_LENGTH],  char time[][6], int low, int high);
void swapSong(char song[][MAX_LENGTH],  char time[][6], int low, int high);

void sortMain(int num) // Main function to sort the list by lexicographic order
{
    int i;

    quickSortArtist(songList, 0, num-1); // Sort artist name

    for(i = 0; i < num; i++) // Sort song name
    {
        quickSortSong(songList[i].songTitle, songList[i].songDuration, 0, songList[i].songCount - 1);
    }
}

void quickSortArtist(LIST list[], int low, int high) // Function of quick sort for artist name
{
    int pivot;

    if(low < high)
    {
        pivot = partitionArtist(list, low, high); // Get pivot
        // Recursive call to sort list by artist name
        quickSortArtist(list, low, pivot - 1);
        quickSortArtist(list, pivot + 1, high);
    }
}

int partitionArtist(LIST list[], int low, int high) // Function of partition for artist name
{
    char *pivotElement;
    int i, j;
    int mid = (low + high) / 2; // Initialize variable mid

    // Median of three
    // If first character of mid string is lexicographically after the first character of high string
    if(strcmp(list[mid].artisteName, list[high].artisteName) > 0)
    {
        swapArtist(list, mid, high); // Swap the mid artist and high artist
    }
    // If first character of low string is lexicographically after the first character of high string
    if(strcmp(list[low].artisteName, list[high].artisteName) > 0)
    {
        swapArtist(list, low, high); // Swap the low artist and high artist
    }
    // If first character of mid string is lexicographically after the first character of low string
    if(strcmp(list[mid].artisteName, list[low].artisteName) > 0)
    {
        swapArtist(list, mid, low); // Swap the mid artist and low artist
    }

    pivotElement = list[low].artisteName; // Assign pivot

    i = low + 1; // Assign i as lower index
    j = high; // Assign j as higher index

    while(i <= j) // Move through whole array to check the order
    {
        // If first character of ith string is lexicographically before the first character of pivot string
        if(strcmp(list[i].artisteName, pivotElement) <= 0)
        {
            i++; // Increment i to move to next index (move to right)
        }
        // If first character of jth string is lexicographically after the first character of pivot string
        else if(strcmp(list[j].artisteName, pivotElement) > 0)
        {
            j--; // Decrement j to ,ove back to previous index (move to left)
        }
        else
        {
            // Swap the artist name and move towards the middle position of array
            swapArtist(list, i, j);
            i++;
            j--;
        }
    }

    swapArtist(list, low, j); // Swap the pivot string with the jth string

    return j;
}

void swapArtist(LIST list[], int low, int high) // Function to swap to artist name and their songs
{
    LIST tmp;

    // Swap the low artist with high artist
    tmp = list[low];
    list[low] = list[high];
    list[high] = tmp;
}

void quickSortSong(char song[][MAX_LENGTH],  char time[][6], int low, int high) // Function of quick sort for song title and their duration
{
    int pivot;

    if(low < high)
    {
        pivot = partitionSong(song, time, low, high); // Get pivot
        // Recursive call to sort the song title
        quickSortSong(song, time, low, pivot - 1);
        quickSortSong(song, time, pivot + 1, high);
    }
}

int partitionSong(char song[][MAX_LENGTH],  char time[][6], int low, int high) // Function of partition for song title and their duration
{
    char *pivotElement;
    int i, j;
    int mid = (low + high) / 2;

    // Median of three
    // If first character of mid string is lexicographically after the first character of high string
    if(strcmp(song[mid], song[high]) > 0)
    {
        swapSong(song, time, mid, high); // Swap the mid song title and duration with high song title and duration
    }
    // If first character of low string is lexicographically after the first character of high string
    if(strcmp(song[low], song[high]) > 0)
    {
        swapSong(song, time, low, high); // Swap the low song title and duration with high song title and duration
    }
    // If first character of mid string is lexicographically after the first character of low string
    if(strcmp(song[mid], song[low]) > 0)
    {
        swapSong(song, time, mid, low); // Swap the mid song title and duration with low song title and duration
    }

    pivotElement = song[low]; // Assign pivot

    i = low + 1; // Assign i as lower index
    j = high; // Assign j as higher index

    while(i <= j) // Move through the song title array to sort their order
    {
        // If first character of ith string is lexicographically before the first character of pivot string
        if(strcmp(song[i], pivotElement) <= 0)
        {
            i++; // Increment i to move to next index (move to right)
        }
        else if(strcmp(song[j], pivotElement) > 0)
        {
            j--; // Decrement j to move back to previous index (move to left)
        }
        else{
            // Swap the artist name and move towards the middle position of array
            swapSong(song, time, i, j);
            i++;
            j--;
        }
    }

    swapSong(song, time, low, j); // Swap the pivot string with the jth string

    return j;
}

void swapSong(char song[][MAX_LENGTH],  char time[][6], int low, int high) // Function to swap two song title and their duration
{
    char tmp[MAX_LENGTH]; // temporary string array

    // Swap song title
    strcpy(tmp, song[low]);
    strcpy(song[low], song[high]);
    strcpy(song[high], tmp);

    // Swap song duration
    strcpy(tmp, time[low]);
    strcpy(time[low], time[high]);
    strcpy(time[high], tmp);
}