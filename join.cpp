#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

void run(int count) {
    while (count-- > 0)
        cout << count << " xuebaobizui" << endl;
    std::this_thread::sleep_for(chrono::seconds(3));
    cout << "thread finished" << endl;
}

int main() {
    std::thread t1(run, 10);
    cout << "main()" << endl;
    // never wait for 3 seconds, because detach means the main thread does not wait for t1
    // one possible thing is that the main thread return too fast making t1 no output
    // we can see that the order of output is in chaos
    if (t1.joinable()) t1.detach(); 
    if (t1.joinable()) t1.detach(); 
    
    if (t1.joinable()) t1.join();
    if (t1.joinable()) t1.join();  // it is not allowed to use double join
    cout << "main() after" << endl; 
    std::this_thread::sleep_for(chrono::seconds(3));
    return 0;
}