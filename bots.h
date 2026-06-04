// Programmers: Julie Tong and Ryan Dong

// Julie Tong's Class Account Username:
// Ryan Dong's Class Account Username: cssc3118

// Class Information: CS480, Summer 2026

// Assignment Information: Programming Assignment 1

// Filename: bots.h

#ifndef BOTS_H
#define BOTS_H

#include <pthread.h>
#include <semaphore.h>

// number of bot threads required
const int NUM_THREADS = 7;

// iterations of each thread write
const int NUM_WRITES = 8;

// shared semaphore
// used to protect quote file
extern sem_t FLAG;

// data passed to each thread
struct ThreadData {
    int threadNumber;
};

// thread function
void* botThread(void* arg);

#endif
