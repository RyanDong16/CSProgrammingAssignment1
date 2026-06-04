// Programmers: Julie Tong and Ryan Dong

// Julie Tong's Class Account Username:
// Ryan Dong's Class Account Username: cssc3118

// Class Information: CS480, Summer 2026

// Assignment Information: Programming Assignment 1

// Filename: main.cpp

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include "bots.h"

using namespace std;

int main() {
    // create QUOTE.txt before threads start writing
    ofstream outFile;
    outFile.open("QUOTE.txt");

    if (!outFile) {
        cerr << "ERROR: could not open QUOTE.txt" << endl;
        return 1;
    }

    // write process ID to file
    outFile << "Process ID: " << getpid() << endl;
    outFile.close();

    // initialize semaphore
    sem_init(&FLAG, 0, 1);

    // create thread arrays
    pthread_t threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS];

    // create bot threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threadData[i].threadNumber = i + 1;

        cout << "Creating thread, in main(): " << threadData[i].threadNumber << endl;

        int result = pthread_create(
            &threads[i],
            nullptr,
            botThread,
            &threadData[i]
        );

        if (result != 0) {
            cerr << "ERROR: could not create thread "
                 << threadData[i].threadNumber
                 << endl;
            return 1;
        }
    }

    // wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], nullptr);
    }

    // destroy semaphore
    sem_destroy(&FLAG);

    cout << "All threads finished writing to QUOTE.txt" << endl;

    return 0;
}
