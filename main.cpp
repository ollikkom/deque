#include <iostream>
#include "Deque.h"

int main() {
    Deque <int> obj(8.0);
    Deque <int> L(5.0);
    L.push_front(1); L.push_front(2); L.push_front(3);
    std::cout<< L.size()<<std::endl;

    Deque<int>::Iterator i;
    for( auto i = L.begin(); i != L.end();++i ) {
        std::cout<<">> "<<(*i)<<std::endl;
    }

    std::cout<< "Next level: " <<std::endl;
    L.push_back(1); L.push_back(3); L.push_back(5);
    for( auto i = L.begin(); i != L.end();++i ) {
        std::cout << ">> " << (*i) << std::endl;
    }
    std::cout << L.size() << std::endl;

    std::cout<< "Next level(reverse): " <<std::endl;
    i = L.end();
    while(i != L.begin()){
        --i;
        std::cout<<">> "<<(*i)<<std::endl;
    }

    std::cout<< "Next level: " <<std::endl;
    L.pop_front(); L.pop_front();
    for( auto i = L.begin(); i != L.end();++i ) {
        std::cout << ">> " << (*i) << std::endl;
    }
    std::cout << L.size() << std::endl;

    std::cout<< "Next level: " <<std::endl;
    L.pop_back();
    for( auto i = L.begin(); i != L.end();++i ) {
        std::cout << ">> " << (*i) << std::endl;
    }
    std::cout << L.size() << std::endl;
    //std::cout << "Hello, World!" << std::endl;
//    for(auto it= obj.begin(); it != obj.end(); ++it)
//    {
//        std::cout<< "iterator"<<(*it)<<std::endl;
//    }
    return 0;
}