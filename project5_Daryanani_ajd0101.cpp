/*
* FILE NAME:project5_Daryanani_ajd0101.cpp
* AUTHOR: Daryanani, Armaan (ajd0101)
* VERSION: 07/28/2023
* DESCRIPTION: COMP2710 Software Construction Project 5
* COMPILE: g++ project5_Daryanani_ajd0101.cpp -o Project5.out
* RUN: ./Project5.out
*/

#include <iostream>
#include <thread>
#include <queue>
#include <condition_variable>
#include <chrono>
#include <ctime>
#include <atomic>

using namespace std;

//declares a mutex and a condition variable
mutex mtx;
condition_variable cv;

//declares a shared buffer
queue<int> buffer;
const unsigned int BUFFER_SIZE = 3;

//handles termination
atomic<bool> terminateThreads(false);

//function for Producer thread
void producer()
{
    while(!terminateThreads)
    {
        //locks the mutex
        unique_lock<mutex> lock(mtx);

        //wait until buffer is not full or terminated
        cv.wait(lock, []{ return buffer.size() != BUFFER_SIZE || terminateThreads; });

        //check for termination request
        if (terminateThreads) break;

        //generate a random value
        int val = rand() % 100;

        //push the value into the buffer
        buffer.push(val);
        cout << "Produced " << val << endl;

        //notify the other thread
        cv.notify_one();

        //sleep for a random time to introduce randomness
        this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
    }
}

//function for Consumer thread
void consumer()
{
    while(!terminateThreads)
    {
        //lock the mutex
        unique_lock<mutex> lock(mtx);

        //wait until buffer is not empty or terminated
        cv.wait(lock, []{ return !buffer.empty() || terminateThreads; });

        //check for termination request
        if (terminateThreads && buffer.empty()) break;

        //consume the value and pop it from the buffer
        cout << "Consumed " << buffer.front() << endl;
        buffer.pop();

        //notify the other thread
        cv.notify_one();

        //sleep for a random time to introduce randomness
        this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
    }
}

int main()
{
    srand((unsigned) time(0));

    //create producer and consumer threads
    thread prod(producer);
    thread cons(consumer);

    //allow the threads to run for a certain amount of time (10 seconds here)
    this_thread::sleep_for(chrono::seconds(10));

    //request termination
    terminateThreads = true;
    cv.notify_all(); //wakes up both threads

    //join the threads
    prod.join();
    cons.join();

    return 0;
}

/*****************EXPLAINATION*****************/
/*
 * The program creates one producer and one consumer thread in the main function by calling `thread prod(producer)` and `thread cons(consumer)`
 *
 * The shared buffer is a queue object `buffer` that is accessible by both threads. A mutex `mtx` and a condition variable `cv` are used to ensure that only one of the producer/consumer can access the buffer at any given time
 *
 * The shared buffer can store at least 3 elements, indicated by the `BUFFER_SIZE` constant set to 3. The `cv.wait()` function ensures that the producer does not add to the buffer if it is full and the consumer does not consume from the buffer if it is empty.
 *
 * The producer thread generates at most 1 element before releasing control of the shared buffer. This is done in the `producer()` function where one element is pushed onto the buffer and then the control is released by notifying the condition variable
 *
 * The consumer thread consumes at most 1 element before releasing control of the shared buffer. This is done in the `consumer()` function where one element is popped from the buffer and then the control is released by notifying the condition variable.
 *
 * Special cases such as when the shared buffer is empty/full are properly handled by the `cv.wait()` function call in both the producer and consumer functions, which block until the buffer is not full or not empty
 *
 * The program outputs readable print statements displaying the activity of the producer and consumer threads. This is done in the `producer()` and `consumer()` functions with `cout`.
 *
 * The simulation gracefully terminates the program after 10 seconds, which can be changed inside the main function
 */
