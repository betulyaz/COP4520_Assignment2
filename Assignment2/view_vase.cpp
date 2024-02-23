#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <array>
#include <chrono>
#include <set>

#define GUESTS 30
using namespace std;
mutex mtx;

//Store the guests who have already viewed in a set to avoid duplicates.
set<thread::id> guestsVisited{};
unsigned int guest_count = 0;


//Room Status
enum Status{
    AVAILABLE,
    BUSY
};

//Set room status to available for the first guest.
Status room_status = Status::AVAILABLE;

//Random function to simulate time required for viewing
unsigned int view_timer(int min, int max){

    return rand() % (max - min + 1) + min;

}


void view_vase(int threadIndex){

    thread::id threadID = this_thread::get_id();

    while (guest_count < GUESTS){

        mtx.lock();

        if (room_status == Status::AVAILABLE && guestsVisited.find(threadID) == guestsVisited.end()){

            //Set room status to Busy since we have a guest inside
            room_status = Status::BUSY;
            cout << "Guest #" << threadIndex << " is viewing the vase" << endl;

            //simulate time needed for viewing the vase
            this_thread::sleep_for(chrono::milliseconds(view_timer(50, 200)));
            guestsVisited.insert(threadID);
            guest_count++;

            //Set the room status to available for the next guest
            room_status = Status::AVAILABLE;
        }

        mtx.unlock();
    }
}

int main(){

    //initialize the timer

    clock_t startTimer, stopTimer;
    array<thread, GUESTS> threads{};

    startTimer = clock();

    //spawn the threads
    for (size_t i = 0; i < threads.size(); i++){

        threads[i] = thread(view_vase, i);
    }

    //join the threads
    for (auto &thread : threads){

        thread.join();
    }

    stopTimer = clock();

    cout << "All "<< guest_count <<" guests have viewed the vase." << endl;
    cout << "Finished in " << stopTimer - startTimer << "milliseconds" << endl;
}
