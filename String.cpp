#include <iostream>
#include <string.h>

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
        String(iterator begin,iterator end);

        //普通函数
        char *c_str() const;
        size_t size() const;

        //运算符重载函数
        
        //比较函数
        bool operator==(String &s2);        
        bool operator!=(String &s2);

        bool operator<(String &s2);
        bool operator<=(String &s2);
        bool operator>(String &s2);
        bool operator>=(String &s2);
               

        //合并函数

        String operator+(const String &s2);
        String operator+(const char *str);

        //赋值操作
        String &operator=(String &s2);
        String &operator=(const char *str);

        String operator+=(String &s2);
        String operator+=(const char *str);
        
            
        //析构函数
        ~String();

        //迭代器操作
        iterator begin() const{
            return iterator(this,0);
        }
        iterator end() const{
            return iterator(this,length);
        }

        //迭代器类
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
                    //判断是否指向同一对象
                    if(this->it != end.it)
                        return -1; 
                    else {
                        return this->index - end.index;
                    }
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
                    if(index+1 > it->size()) {
                        cout << "无法递增,无效的迭代器" << endl;
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
                        cout << "无法递减,无效的迭代器" << endl;
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
                    ++(*this);
                    return its;
                }
                //后置递减
                iterator operator--(int num) {
                    //保存当前迭代器状态
                    iterator its = *this;
                    --(*this);
                    return its;
                }
                
                //小于大于
                bool operator<(iterator &its) {
                    //判断是否指向同一String对象
                    if(this->it != its.it) {
                        cout << "指向不同对象的迭代器不能互相比较" << endl;
                        exit(0);
                    }
                    return this->index < its.index;
                }
                bool operator<=(iterator &its) {
                    //判断是否指向同一String对象
                     if(this->it != its.it) {
                        cout << "指向不同对象的迭代器不能互相比较" << endl;
                        exit(0);
                    }
                    return this->index <= its.index;
                }
                bool operator>(iterator &its) {
                    return !(*this < its);
                }
                bool operator>=(iterator &its) {
                    return !(*this <= its);
                }

                //累加累减
                iterator &operator+=(int num) {
                    if(this->index+num > this->it->size()) {
                        cout << "无法增长，无效的迭代器" << endl;
                        exit(0);
                    }
                    this->index += num;
                    return *this;
                }  
                iterator &operator-=(int num) {
                    if(this->index-num < 0) {
                        cout << "无法减少，无效的迭代器" << endl;
                        exit(0);
                    }
                    this->index -= num;
                    return *this;
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
    cout << "3" << endl;
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
    cout << "1" << endl;
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

String::String(iterator begin,iterator end)
{
    //判断是否指向同一对象并且迭代器范围是否有误
    if(end - begin < 0) {
        cout << "length=" << end - begin << endl;
        cout << "无效的迭代器" << endl;
        exit(0);
    } 
    else {
        data = new char[end - begin+1];
        size_t i = 0;
        while(begin != end) {
            data[i++] = *begin++;
        }
        data[i] = '\0';
    }
}

bool String::operator==(String &s2)
{
    if(this->length != s2.size())
    return false;
    for(size_t i = 0;i < this->length;++i) {
        if(data[i] != s2.c_str()[i])
            return false;
    }
    return true;
}  

bool String::operator<(String &s2) 
{
    size_t n = 0;
    while(n < this->length && n < s2.size()) {
        if(this->c_str()[n] != s2.c_str()[n])
            return this->c_str()[n] < s2.c_str()[n];
        n++;
    }
    if(n == this->length && n == s2.size())
        return false;
    else if(n == s2.size())
        return false;
    else
        return true;
}

bool String::operator<=(String &s2) 
{
    size_t n = 0;
    while(n < this->length && n < s2.size()) {
        if(this->c_str()[n] != s2.c_str()[n])
            return this->c_str()[n] < s2.c_str()[n];
        n++;
    }
    if(n == this->length && n == s2.size())
        return true;
    else if(n == s2.size())
        return false;
    else
        return true;
}
bool String::operator>(String &s2) 
{
    return !(*this < s2); 
}
bool String::operator>=(String &s2) 
{
    return !(*this <= s2);
}

bool String::operator!=(String &s2) 
{
    return !(*this == s2);
}

String String::operator+(const String &s2)
{
    
    long l = this->length + s2.size();
    char ar[l];

    strcpy(ar,this->c_str());
    strcat(ar,s2.c_str());

    String temp2(ar);
    return temp2;
    
}
String String::operator+(const char *str) 
{
    String s2(str);
    long l = this->length + s2.size();
    char ar[l];

    strcpy(ar,this->c_str());
    strcat(ar,s2.c_str());

    String temp2(ar);
    return temp2;

} 

String &String::operator=(const char *str) 
{
    cout << "4" << endl;
    //检查字符串是否有效
    if(!str) {
        String(); 
    }
    //检查当前String类是否有数据
    if(this->length > 0) {
        delete(this->data);
    }
    this->length = strlen(str);
    data = new char[strlen(str)+1];
    strcpy(data,str);;
    data[this->length] = '\0';
    return *this;
}

String &String::operator=(String &s2)
{
    cout << "2" << endl;
    return *this = s2.c_str();
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
        

    
    String s4;
    s4 = "wh";
    String s5 = "wh";

    return 0;
}

