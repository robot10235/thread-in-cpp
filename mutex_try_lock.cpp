// std::mutex::try_lock() is non blocking
// compared to lock() if the lock has not been released, it would block actually 

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int counter = 0;
std::mutex mtx;

void increasTheCounterFor10000Time() {
    for (int i = 0; i < 100000; ++i) {
        if (mtx.try_lock()) {
            ++counter;
            mtx.unlock();
        }
    }
}

int main() {
    std::thread t1(increasTheCounterFor10000Time);
    std::thread t2(increasTheCounterFor10000Time);

    t1.join();
    t2.join();
    cout << " counter could increases upto: " << counter << endl;
    return 0;
}