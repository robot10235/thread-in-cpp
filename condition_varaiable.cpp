/*
 * condition varable are used for 
 * 1. notify other threads  
 * 2. waiting for some conditions
 *  need to use mutex to use condition variable
 * 
 * NOTE:
 * 1. condition variables are used to synchronize tow or more threads
 * 2. Best use case of condition variable is Producer / Consumer problem
 * 3. mutex lock is used for share memory model like modify the same variable
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

std::condition_variable cv;
std::mutex m;
long balance = 0;

void addMoney(int money) {
    std::lock_guard<mutex> lg(m);
    balance += money;
    cout << "Amount Added Current Balance: " << balance << endl;
    // notify_one means waken one random thread
    // notify_all means waken all threads, and they need to race 
    cv.notify_one();
}

void withdrawMoney(int money) {
    std::unique_lock<mutex> ul(m);
    // wait for the lock release and the condition
    // although the lock is available, the conditions is not right
    // t1 has to sleep
    cv.wait(ul, [] { return (balance != 0) ? true : false; });
    if (balance >= money) {
        balance -= money;
        cout << "Amount Deducted: " << money << endl;
    }
    else {
        cout << "Amount Can't Be Deducted, Current Balance Is Less Than " << money << endl;
    }
    cout << "Current Balance Is: " << money << endl;
}

int main() {
    std::thread t1(withdrawMoney, 500);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::thread t2(addMoney, 500);
    // t1 would wait until t2 finished, since there's no money in the account
    t1.join();
    t2.join();
    return 0;
}