#include <iostream>
#include <memory>
#include <utility>

template<typename T> class Shared_ptr{
public:
    //构造函数
    Shared_ptr() :ptr(NULL),use_count(NULL) {  }
    Shared_ptr(T *p) : ptr(p),use_count(new size_t(1)){  }

    //拷贝构造函数
    Shared_ptr(Shared_ptr<T> &p);

    //拷贝赋值运算符
    Shared_ptr<T> operator=(Shared_ptr<T> &q);

    size_t Use_count() { return *use_count; }

    //析构函数
    ~Shared_ptr();
private:
    size_t *use_count;
    T *ptr;

};

template<typename T> 
Shared_ptr<T>::~Shared_ptr<T>()
{
    *use_count--;
    if(*use_count == 0)
        delete(ptr);
}
template<typename T>    
Shared_ptr<T>::Shared_ptr(Shared_ptr<T> &p)
{
    this->ptr = p.ptr;
    //拷贝构造时引用计数加一
    (*p.use_count)++;
    this->use_count = p.use_count;
}
template <typename T>
Shared_ptr<T> Shared_ptr<T>::operator=(Shared_ptr<T> &q)
{
    //拷贝赋值时被赋值方原有对象引用计数减一
    (*this->use_count)--;
    //赋值方对象引用计数加一
    (*q.use_count)++;
    this->ptr = q.ptr;
    this->use_count = q.use_count;
}
int main()
{
    int i = 10;
    Shared_ptr<int> p(&i);
    auto q = p;
    int j = 0;
    Shared_ptr<int> m(&j);
    m = p;
    std::cout << q.Use_count() << std::endl;
    return 0;
}

