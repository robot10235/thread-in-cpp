/*
 * same thread can lock one mutex multiple times using recursive_mutex
 * if thread T1 first lock on recursive mutex m1, then m1 is locked by T1
 * not as T1 is running in recursion T1 can call lock/ try_lock any number of times.
 * 
 * But if T1 acquired k times lock on mutex m1, then T1 have to unlock it k times 
 * otherwise no other thread will be able to lock mutex m1
 * 
 */

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;


std::recursive_mutex m1;
int buffer = 0;

void recursion(char c, int loopFor) {
    if (loopFor < 0) {
        return;
    }
    m1.lock();
    cout << "ThreadID: " << c << " " << buffer++ << endl;
    recursion(c, --loopFor);
    m1.unlock();
    cout << "unlock by thread " << c << endl;
}

int main() {
    thread t1(recursion, '1', 10);
    thread t2(recursion, '2', 10);
    t1.join();
    t2.join();
    return 0;
}