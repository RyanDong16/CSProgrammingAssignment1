// Programmers: Julie Tong and Ryan Dong

// Julie Tong's Class Account Username:
// Ryan Dong's Class Account Username: cssc3118

// Class Information: CS480, Summer 2026

// Assignment Information: Programming Assignment 1

// Filename: bots.cpp

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include "bots.h"

using namespace std;

// define global semaphore
sem_t FLAG;

void* botThread(void* arg) {
    // cast arg back to ThreadData*
    ThreadData* data = static_cast<ThreadData*>(arg);

    // get thread number
    int threadNum = data->threadNumber;

    // each bot writes to the quote file NUM_WRITES times
    for (int i = 0; i < NUM_WRITES; i++) {
        // even threads sleep 2 seconds
        if (threadNum % 2 == 0) {
            sleep(2);
        }
        // odd threads sleep 3 seconds
        else {
            sleep(3);
        }

        // wait on semaphore before entering critical section
        sem_wait(&FLAG);

        // open QUOTE.txt in append mode
        ofstream outFile;
        outFile.open("QUOTE.txt", ios::app);

        if (!outFile) {
            cerr << "ERROR: could not open QUOTE.txt" << endl;
            sem_post(&FLAG);
            pthread_exit(nullptr);
        }

        // write thread number and correct quote
        if (threadNum % 2 == 0) {
            outFile << "Thread " << threadNum << ": "
                    << "\"Controlling complexity is the essence of computer programming.\" --Brian Kernighan"
                    << endl;
        }
        else {
            outFile << "Thread " << threadNum << ": "
                    << "\"Computer science is no more about computers than astronomy is about telescopes.\" --Edsger Dijkstra"
                    << endl;
        }

        // print thread to stdout
        cout << "Thread " << threadNum << " is running" << endl;

        // close QUOTE.txt
        outFile.close();

        // release semaphore
        sem_post(&FLAG);
    }

    // exit thread
    pthread_exit(nullptr);
}
