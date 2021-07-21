//
// Created by User on 10/3/2021.
//

#ifndef MAIN_C_RANDOMIZEDLIST_H
#define MAIN_C_RANDOMIZEDLIST_H

void charToInt(int count);
void randomisedPlaylistMain(int count);
int randomise(int count);
void checkSong(int *count, int *total);
int pickSong(int total, int *randNum);
int ifTriplePlay(char str[], int total, int randNum);
void printPlaylist(char str[], int j, int *counter, int *duration, int index);
void printSong(int *duration, int i, int j);
void printDuration(int duration);

#endif //MAIN_C_RANDOMIZEDLIST_H
