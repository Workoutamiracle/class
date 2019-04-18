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
int main()
{
    int i = 10;
    shared_ptr<int> q;
    q = make_shared<int>(i);
    shared_ptr<int> p = q;
    std::cout << *q << std::endl;
    return 0;
}

