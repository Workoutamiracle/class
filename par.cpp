#include <iostream>
#include <string>

using namespace std;
int main()
{
    string s1("wangheng");
    auto p = s1.begin()+2;
    auto q = s1.begin()+6;

    if(p == q)
        cout << "相等" << endl;
    else
        cout << "不相等" << endl;



}

