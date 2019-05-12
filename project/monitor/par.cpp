#include <iostream>
#include <fstream>

int main()
{
    char filename[100] = {'\0'};
    std::cin >> filename;

    std::fstream file(filename,std::ios::out);
    
    if(file.is_open())
        std::cout << "open" << std::endl;
    else
        std::cout << "not" << std::endl;
    file << "123456";
    file.close();
    return 0;
}

