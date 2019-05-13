#include <iostream>
#include <fstream>

int main()
{
    char filename[100] = {'\0'};
    std::cin >> filename;

    std::fstream file(filename,std::ios::out);
    
    file << "12345678";
    file.close();
    return 0;
}

