#include <iostream>
#include <vector>
#include <memory>
using namespace std;
int main()
{
    vector<int> vec = {1,2,3};
    auto p = make_shared<vector<int>>(vec);
    cout << (*p)[2] << endl;

    return 0;
}

