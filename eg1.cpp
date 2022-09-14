#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;
typedef unsigned long long ull;

ull OddSum = 0;
ull EvenSum = 0;

void findEven(ull start, ull end) {
    for (ull i = start; i <= end; ++i) {
        if ((i & 1) == 0) {
            EvenSum += i;
        }
    }
}

void findOdd(ull start, ull end) {
    for (ull i = start; i <= end; ++i) {
        if ((i & 1) == 1) {
            OddSum += i;
        }
    }
}

int main() {
    ull start = 0;
    ull end = 1900000000;

    auto startTime = high_resolution_clock::now();



    /* join means join t1 to the main thread
     * if we do not use join, when the main thread finish
     * and t1 is still running, the program will return and we cannot get t1 result.
     */    
    std::thread t1(findEven, start, end);
    std::thread t2(findOdd, start, end);
    t1.join();
    t2.join();

    // findEven(start, end);
    // findOdd(start, end);

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stopTime - startTime);

    cout << "OddSum : " << OddSum << endl;
    cout << "EvenSum : " << EvenSum << endl;

    // benchmark
    cout << "Sec: " << duration.count() << endl;

    return 0;
}