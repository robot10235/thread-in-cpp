#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int myAmount = 0;
std::mutex m;

void addMoney() {
    // avoid race condition
    m.lock();
    ++myAmount;
    m.unlock();
}

int main() {
    std::thread t1(addMoney);
    std::thread t2(addMoney);

    // race condition
    t1.join();
    t2.join();

    cout << myAmount << endl;
    return 0;
}