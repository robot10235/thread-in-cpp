#include <iostream>
#include <thread>

using namespace std;

void func(int x) {
    cout << x << endl;
}

class Base {
 public:
  static void run2(int x) { cout << x << endl; }
  void run(int x) { cout << x << endl; }
  void operator ()(int x) { cout << x << endl; }
}

int main() {

    // lambda
    auto func = [](int x) {
        cout << x << endl;
    };    
    std::thread t1(func, 10);
    t1.join();

    // function pointer
    std::thread t1(func, 10);
    t1.join();

    // functor
    std::thread t1((Base()), 10);
    t1.join();

    // non static member function
    Base b; // because it is not a static function it needs a object
    std::thread t1(&Base::run, &b, 10);
    t1.join();

    // static member function
    std::thread t1(&Base::run2, 10);
    t1.join();
    
    return 0;
}