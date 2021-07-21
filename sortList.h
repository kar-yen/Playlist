//
// Created by User on 27/2/2021.
//

#ifndef ASSIGNMENT1_SORTLIST_H
#define ASSIGNMENT1_SORTLIST_H
#define MAX_LENGTH 100

void sortMain(int num);
void quickSortSong(char song[][MAX_LENGTH], char time[][6], int low, int high);
int partitionSong(char song[][MAX_LENGTH],  char time[][6], int low, int high);
void swapSong(char song[][MAX_LENGTH],  char time[][6], int low, int high);

#endif //ASSIGNMENT1_SORTLIST_H
