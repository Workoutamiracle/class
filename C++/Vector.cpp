#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <initializer_list>
#include <algorithm>

template <typename T> class Vector{
public:
    //构造函数
    Vector() : elements(NULL),first_free(NULL),cap(NULL) {  };
    Vector(const Vector<T> &);  //拷贝构造函数
    Vector &operator=(const Vector<T> &);   //拷贝赋值运算符
    ~Vector() { this->free(); };                  //析构函数

    //
    void push_back(const T &);

    size_t size() { return first_free - elements; }
    size_t capacity() { return cap - elements; }

    //迭代器操作
    T *begin() { return elements; };
    T *end() { return first_free; }; 
    
private:
    std::allocator<T> alloc; //用于分配内存空间的分配器
    //检查已有空间大小,若溢出则分配另外的空间
    void check_n_alloc() { if(size() == capacity()) reallocate(); }
    void free();//销毁元素并且释放内存
    void reallocate();//获取更多内存并拷贝已有元素
    
    std::pair<T*,T*> alloc_n_copy(const T*,const T*);
    T *elements;//指向首元素
    T *first_free;//指向已分配空间的未构造位置
    T *cap;     //指向尾元素
};

template <typename T>
void Vector<T>::push_back(const T &t)
{
    //检查空间是否足够
    check_n_alloc();
    //在first_free指向的空间中构造元素
    alloc.construct(first_free++,t);
}

template<typename T>
std::pair<T*,T*> Vector<T>::alloc_n_copy(const T *b,const T *e)
{
    //分配新的空间
    auto data = alloc.allocate(e-b);
    //将b,e范围内的元素拷贝到以data为起始位置的已分配空间上并返回起始地址和尾部地址
    return {data,uninitialized_copy_n(b,e,data)};
}
template <typename T>
void Vector<T>::free()
{
    if(elements) {
        //对所有已构造的空间执行析构函数
        for(auto p = first_free;p >= elements;--p)
            alloc.destroy(p);
        //回收空间
        alloc.deallocate(elements,cap-elements);

    }
}
template <typename T>    
void Vector<T>::reallocate()
{
    //计算需要申请多少空间
    auto newcapacity = size()?2*size():1;
    //申请空间
    auto newdata = alloc.allocate(newcapacity);
    //将数据从旧内存移动到新内存
    auto dest = newdata;
    auto elem = elements;
    for(size_t i = 0;i < size();++i)
        alloc.construct(dest++,std::move(*elem++));
    //释放旧空间
    this->free();
    //更新指针指向
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}
template <typename T>
Vector<T>::Vector(const Vector<T> &V)
{
    auto newdata = alloc_n_copy(V.begin(),V.end());
    elements = newdata.first;
    cap = first_free = newdata.second;
}
template <typename T>
Vector<T>&  Vector<T>::operator=(const Vector<T> &V)
{
    auto data = alloc_n_copy(V.begin(),V.end());
    this->free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

int main()
{
    Vector<std::string> v1;
    v1.push_back("wh");
    v1.push_back("gl");
    auto p = v1.begin();
    ++p;
    std::cout << *p << std::endl;

    return 0;
}

