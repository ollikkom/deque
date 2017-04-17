#include <iostream>
#include "TDeque.h"

int main() {
    Deque <int> obj(8.0);

    //std::cout << "Hello, World!" << std::endl;
    for(auto it= obj.begin(); it != obj.end(); ++it)
    {
        std::cout<< "iterator"<<(*it)<<std::endl;
    }
    return 0;
}