#include <iostream>
#include <string.h>

using namespace std;
class String{
    private:
        size_t length;
        char *data;
    public:
        //构造函数
        String();
        String(size_t length,char ch);
        String(const char *str);
        String(const char *str,size_t length);
        String(String &str);
        String(String &str,size_t index,size_t length);

        //
        char *c_str() const;
        size_t size() const;

    };
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
    String s1;
    String s2(5,'w');
    String s3("wwwww");
    String s4("wwwwww",5);
    String s5(s2);
    String s6(s4,0,5);

    cout << s1;
    cout << s3 << endl;
    cout << s4 << endl;
    cout << s5 << endl;
    cout << s6 << endl;

    return 0;
}

