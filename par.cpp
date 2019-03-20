#include <iostream>
#include <string>

using namespace std;
int main()
{
    string s1("wangheng1");
    string s2 = "wangheng"; 
    
    cout << s1+"wangheng" << endl;
    cout << s1+s2<< endl;
    if(s1 < s2)
        cout << s1 << " 小于 " << s2 << endl;
    else if(s1 == s2)
        cout << s1 << " 等于 " << s2 << endl;
    else
        cout << s1 << " 大于 " << s2 << endl;
}

