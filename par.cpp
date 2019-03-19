#include <iostream>
#include <string>

using namespace std;
int main()
{
    string s1("wangheng");
    auto p = s1.begin();
    auto q = s1.end();
    cout << p-q << endl;
    cout << p+q << endl;


}

