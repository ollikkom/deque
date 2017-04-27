#include <deque>
#include <string>

#define CHECK

#ifdef CHECK
#include "Deque.h"

template<class T>
using deque = Deque<T>;

#else

template<class T>
using deque = std::deque<T>;

#endif // CHECK


#define assert(X) { \
	if(!(X)) {\
		std::cout << "see function:'" << __FUNCTION__ << "' line: " << __LINE__;\
		throw std::logic_error(#X); \
	}\
}

int main()
{
    {
        // check queue
        deque<std::string> m;
        assert(m.empty());

        m.push_back("a");
        m.push_back("b");
        m.push_back("c");
        assert(m.size() == 3);

        assert(m.front() == "a");
        assert(m.front() == "a");
        assert(m.front() == "a");

        auto m1 = m;
        assert(m.front() == "a");

        m1.pop_front();
        m1.pop_front();
        m1.pop_front();
        assert(m1.empty());

        m1.swap(m);
        assert(m.empty());
        assert(m1.size() == 3);

        // abc
        for (auto &v : m1)
        {
            std::cout << v << std::endl;
        }

        assert(m1.back() == "c");

        m1.pop_front();
        assert(m1.front() == "b");

        m1.pop_front();
        assert(m1.front() == "c");

        m1.pop_front();
        assert(m1.empty());
    }

    {
        // check stack
        deque<std::string> m;
        assert(m.empty());

        m.push_front("a");
        m.push_front("b");
        m.push_front("c");
        assert(m.size() == 3);

        assert(m.front() == "c");
        assert(m.front() == "c");
        assert(m.front() == "c");

        auto m1 = m;
        assert(m.front() == "c");

        m1.pop_back();
        m1.pop_back();
        m1.pop_back();
        assert(m1.empty());


        m1.swap(m);
        assert(m.empty());
        assert(m1.size() == 3);

        // cba
        for (auto &v : m1)
        {
            std::cout << v << std::endl;
        }

        assert(m1.back() == "a");

        m1.pop_back();
        assert(m1.back() == "b");

        m1.pop_back();
        assert(m1.back() == "c");

        m1.pop_back();
        assert(m1.empty());
    }
}
//int main() {
//    Deque <int> obj(8.0);
//    Deque <int> L(5.0);
//    L.push_front(1); L.push_front(2); L.push_front(3);
//    std::cout<< L.size()<<std::endl;
//
//    Deque<int>::Iterator i;
//    for( auto i = L.begin(); i != L.end();++i ) {
//        std::cout<<">> "<<(*i)<<std::endl;
//    }
//
//    std::cout<< "Next level: " <<std::endl;
//    L.push_back(1); L.push_back(3); L.push_back(5);
//    for( auto i = L.begin(); i != L.end();++i ) {
//        std::cout << ">> " << (*i) << std::endl;
//    }
//    std::cout << L.size() << std::endl;
//
//    std::cout<< "Next level(reverse): " <<std::endl;
//    i = L.end();
//    while(i != L.begin()){
//        --i;
//        std::cout<<">> "<<(*i)<<std::endl;
//    }
//
//    std::cout<< "Next level: " <<std::endl;
//    L.pop_front(); L.pop_front();
//    for( auto i = L.begin(); i != L.end();++i ) {
//        std::cout << ">> " << (*i) << std::endl;
//    }
//    std::cout << L.size() << std::endl;
//
//    std::cout<< "Next level: " <<std::endl;
//    L.pop_back();
//    for( auto i = L.begin(); i != L.end();++i ) {
//        std::cout << ">> " << (*i) << std::endl;
//    }
//    std::cout << L.size() << std::endl;
//    //std::cout << "Hello, World!" << std::endl;
////    for(auto it= obj.begin(); it != obj.end(); ++it)
////    {
////        std::cout<< "iterator"<<(*it)<<std::endl;
////    }
//    return 0;
//}