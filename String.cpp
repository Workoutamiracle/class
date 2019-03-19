#include <iostream>
#include <string.h>
#include <string>

using namespace std;
class String{
    private:
        size_t length;
        char *data;
    public:
        class iterator;
        //构造函数
        String();
        String(size_t length,char ch);
        String(const char *str);
        String(const char *str,size_t length);
        String(String &str);
        String(String &str,size_t index,size_t length);
        String(iterator &begin,iterator &end);
        //
        char *c_str() const;
        size_t size() const;

        //析构函数
        ~String();

        iterator begin() {
            return iterator(this,0);
        }
        //迭代器
        class iterator{
            public:
                //迭代器构造函数
                iterator() {
                    it = NULL;
                }
                iterator(const iterator &its) {
                        it = its.it;
                        index = its.index;
                }
                iterator(const String *str) {
                    it = str;
                    index = 0;
                }
                iterator(const String *str,size_t num) {
                    if(num < 0) {
                        it = NULL;
                        index = 0;
                    }
                    else {
                        it = str;
                        index = num;
                    }
                }
                
                char operator*() {
                    return *(it->data+index);
                }

                //迭代器加法
                iterator operator+(int num) {
                    if(!it)
                        return iterator();
                    return iterator(it,index+num);
                }
                //迭代器减法
                iterator operator-(int num) {
                    if(!it)
                        return iterator();
                    return iterator(it,index-num);
                }
                //迭代器与迭代器减法
                int operator-(iterator &end) {
                    return this->it->size() - end.it->size();
                }

                iterator &operator=(iterator &its) {
                    it = its.it;
                    index = its.index;
                    return *this;
                } 
                //迭代器相等操作
                bool operator==(iterator &its) {
                    return this->it == its.it && this->index == its.index;
                }
                bool operator!=(iterator &its) {
                    return !(*this == its);
                }
                //前置递增
                iterator &operator++() {
                    if(index+1 >= it->size()) {
                        cout << "无效的迭代器" << endl;
                        exit(0);
                    }
                    else {
                        index += 1;
                    }
                    return *this;
                }
                //前置递减
                iterator &operator--() {
                    if(index-1 < 0) {
                        cout << "无效的迭代器" << endl;
                        exit(0);
                    }
                    else {
                        index -= 1;
                    }
                    return *this;
                }
                //后置递增
                iterator operator++(int num) {
                    //保存当前迭代器状态
                    iterator its = *this;
                    (*this)++;
                    return its;
                }
                //后置递减
                iterator operator--(int num) {
                    //保存当前迭代器状态
                    iterator its = *this;
                    (*this)--;
                    return its;
                }
 

                
                //迭代器析构函数
                ~iterator() {
                    it = NULL;
                }
            private:
                const String *it;
                size_t index;
        };


        

};
String::~String()
{
    delete(data);
}
String::String() 
{
    data = NULL;
    length = 0;
}
String::String(size_t length,char ch)
{
    if(length <= 0) {
        data = NULL;
        length = 0;
        return;
    }
    this->length = length;
    data = new char[length+1];
    for(size_t i = 0;i < length;++i)
        data[i] = ch;
    data[length] = '\0';
}
String::String(const char *str)
{
    if(!str) {
        data = NULL;
        length = 0;
        return;
    }
    else {
        this->length = strlen(str);
        data = new char[this->length+1];
        strcpy(data,str);
        data[length] = '\0';
    }
}
String::String(const char *str,size_t length)
{
    if(!str) {
        data = NULL;
        this->length = 0;
        return;
    }

    if(length > strlen(str)) {
        this->length = strlen(str);
        data = new char[this->length+1];
        strcpy(data,str);
        data[length] = '\0';
  
    }
    else{
        this->length = length;
        data = new char[length+1]; 
        for(size_t i = 0;i < length;++i)
            data[i] = str[i];
        data[length] = '\0';
    }
    
}
String::String(String &str)
{
    if(str.size() == 0) {
        data = NULL;
        this->length = 0;
        return;
    }
    else {
        this->length = str.size();
        data = new char[str.size()+1];
        strcpy(data,str.c_str());
        data[str.size()] = '\0';
    }
}
String::String(String &str,size_t index,size_t length)
{
    if(str.size() == 0 || index < 0) {
        data = NULL;
        this->length = 0;
        return;
    }

    if(length + index > str.size()) {
        this->length = length;
        data = new char[str.size()+1];
        strcpy(data,str.c_str());
        data[str.size()] = '\0';
    }
    else {
        this->length = length;
        data = new char[length+1];
        for(size_t i = index;i < length;++i)
            data[i] = str.c_str()[i];
        data[length] = '\0';
    }
}

String::String(iterator &begin,iterator &end)
{
        
}

char * String::c_str() const
{
    return this->data;
}
size_t String::size() const
{
    return this->length;
}   

ostream& operator<<(ostream &os,const String &str)
{
    if(str.size() == 0) {
        
    }
    else {
        os << str.c_str();
    }
    return os;
}


int main()
{

    return 0;
}

