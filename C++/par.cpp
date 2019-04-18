#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
using namespace std;
std::mutex mtx;
class Foo *X;
class Foo{
public:
    void f() { std::cout << "1" << std::endl; }
};

void fun()
{
    mtx.lock();
    delete X;
    mtx.unlock();
}
void fun2()
{
    mtx.lock();
    X->f();
    mtx.unlock();
}
class A{
public:
    A() { f();}
    virtual void f() { cout << "f" << endl; }
};
class B : public A{
public:
    B() { f(); }
    virtual void f2() { cout << "f2" << endl; }
};
void f(void)
{
    std::cout << "f" << std::endl;
}
class aa{
public:
    aa()=default;
    aa(aa &t) {
        std::cout << "aa1" << std::endl;
    }
    aa &operator=(aa &a) {
        std::cout << "aa2" << std::endl; 
        return *this;
    }
};
int main()
{
    aa a;
    aa a2 = a;
    return 0;
}

