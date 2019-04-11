#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>

template <typename T> 
int compare(const T &v1,const T &v2)
{
    if(v1 > v2)
        return 1;
    else
        return -1;
    return 0;
}

template <typename T,typename U> 
bool Find(const T &it1,const T &it2,const U &val)
{
    T it3 = it1;
    for(;it3 != it2;it3++)
        if(*it3 == val)
            return true;
    return false;
}

template <typename T>
void print(const T &ar)
{
    for(auto n : ar)
        std::cout << n << " ";
}
template <typename T,unsigned N>
const T *begin(const T (&arr)[N])
{
    return arr;
}

template <typename T,unsigned N>
const T *end(const T (&arr)[N])
{
    return arr+N;
}

template <typename T,unsigned N>
constexpr size_t Size(const T (&arr)[N])
{
    return N;
}

template <typename T> class Blob{
    template <typename X> friend class BlobPtr;
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    //构造函数
    Blob() : data(std::make_shared<std::vector<T>>()) {  };
    Blob(std::initializer_list<T> i1) : data(std::make_shared<std::vector<T>>(i1)) {  };
    //Blob中的元素数目
    size_type size() const {return data->size();}
    bool empty()const { return data->empty(); }
    //添加和删除元素
    void push_back(const T &t) {data->push_back(t);}
    void pop_back() { check(0,"pop_back on empty Blob"); data->pop_back(); }
    
    //元素访问
    T &back() { check(0,"back on empty Blob"); return data->back(); };
    T &operator[](size_type i) {  check(i,"subscript out of range"); return (*data)[i]; };
private:
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i,const std::string &msg) const;
};

template <typename T>
void Blob<T>::check(size_type i,const std::string &msg) const
{
    if(i >= data->size())
        throw std::out_of_range(msg);
}

template <typename T> class BlobPtr{
public:
    typedef typename std::vector<T>::size_type size_type;
    //构造函数
    BlobPtr();
    BlobPtr(Blob<T> &a,size_t sz = 0) : wptr(a.data),curr(sz) {  }
    //解引用运算符
    T& operator*()const {auto p = check(curr,"dereference past end"); return (*p)[curr];}
    //递增递减运算符
    BlobPtr operator++();
    BlobPtr operator--();
private:
    std::shared_ptr<std::vector<T>> check(size_type,const std::string&) const;
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;
};
template <typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(size_type i,const std::string& msg) const
{
    auto p = wptr.lock();
    if(i >= p->size())
        throw std::out_of_range(msg);
    return p;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator++()
{
    BlobPtr ret = *this;
    ++*this;
    return ret;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator--()
{
    BlobPtr ret = *this;
    --*this;
    return ret;
}


int main()
{
    Blob<std::string> b = {"123","456","789"};
    BlobPtr<std::string> p(b,0);
    std::cout << *p << std::endl;
    return 0;
}

