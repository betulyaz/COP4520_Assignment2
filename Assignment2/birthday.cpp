#include <algorithm>
#include <iostream>
#include <thread>
#include <mutex>
#include <array>
#include <chrono>
#include <random>

#define GUESTS 30
using namespace std;
mutex mtx;


//counter for number of guests who eat the cupcake.
unsigned int guest_count = 0;
unsigned int CurrentThread;

//Keep track of the cupcake and  guests who have eaten the cupcake.
array<bool, GUESTS > hasEatenCupcake;
bool isCupcakeAvailable = true;


// Use bounds for min and max for the number of guests
// Simulate Random calling the guests as the Minotaur would
unsigned int MinotaursCall(int min, int max) {
	return rand() % (max - min + 1) + min;
}



void navigateLabyrinth(unsigned int threadIndex) {
    while (guest_count < GUESTS ) {
        mtx.lock();

        if (threadIndex == 0) {

            // Make sure the first guest to enter eat only once
            if (isCupcakeAvailable && !hasEatenCupcake[threadIndex]) {
                cout << "Guest #" << threadIndex << " ate the cupcake!" << endl;
                hasEatenCupcake[threadIndex] = true;
                isCupcakeAvailable = true;
                guest_count++;



            }
            // put the first guest in charge of counting and replacing the cupcake.
            else if (!isCupcakeAvailable) {
                isCupcakeAvailable = true;
                guest_count++;


            }

        }
        //Make sure the other  guests eat the cupcake once.
        else if (CurrentThread == threadIndex && isCupcakeAvailable && !hasEatenCupcake[threadIndex]) {
            cout << "Guest #" << threadIndex << " ate the cupcake!" << endl;
            hasEatenCupcake[threadIndex] = true;
            isCupcakeAvailable = false;
        }

        mtx.unlock();
    }
}

int main() {
    clock_t startTimer, stopTimer;
    array<thread, GUESTS> threads{};


    //Start the timer
    //Spawn the threads
    startTimer = clock();
    for (size_t i = 0; i < threads.size(); i++) {
        threads[i] = thread(navigateLabyrinth, i);
    }

    // let the minotaur call the guests in random
    while (guest_count < GUESTS) {
        CurrentThread = MinotaursCall(0, GUESTS);
    }

    //Join the threads
    for (auto& thread : threads) {
        thread.join();
    }

    stopTimer = clock();
    cout << "All " << guest_count << " guests entered the labyrinth." << endl;
    cout << "Game finished in " << stopTimer - startTimer << " milliseconds" << endl;
}
