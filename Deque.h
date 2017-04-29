#ifndef DEQUE_TDEQUE_H
#define DEQUE_TDEQUE_H

#include <iostream>
#include <exception>

class DequeEmptyException {
public:
    DequeEmptyException() {
        std::cout << "Deque empty" << std::endl;
    }
};

template<class T>
class Deque {
    class Elem;

public:
    class Iterator {
        friend class Deque<T>;

        Iterator(Elem *el) : the_elem(el) {}

    public:
        //Iterator():the_elem(0){}
        //Iterator(const Iterator &it):the_elem(it.the_elem){}
        Iterator() = default;

        Iterator &operator=(const Iterator &) = default;

        bool operator==(const Iterator &it) const {
            return (the_elem == it.the_elem);
        }

        bool operator!=(const Iterator &it) const {
            return !(it == *this);
        }

        Iterator &operator++() {
            if ((the_elem != 0) && (the_elem->Next != 0))
                the_elem = the_elem->Next;
            return *this;
        }

        Iterator &operator--() {
            if ((the_elem != 0) && (the_elem->Prev != 0))
                the_elem = the_elem->Prev;
            return *this;
        }

        T &operator*() const {
                return the_elem->Value;
        }

    private:
        Elem *the_elem;
    };

private:
    using value_type = T;
    using size_type = size_t;
    using iterator = Iterator;
    using const_iterator = const Iterator;
    using reference = value_type &;
    using const_reference = const value_type &;

public:
    Deque() : Front(new Elem()), Rear(Front), Count(0) {
        Rear->Next = Rear->Prev = 0;
        ffront = Iterator(Front);
        rear = Iterator(Rear);
    }


    Deque(const value_type &a) : Front(new Elem()), Rear(Front), Count(0) {
        Rear->Next = Rear->Prev = 0;
        ffront = Iterator(Front);
        rear = Iterator(Rear);
        push_front(a);
    }

    /*Deque &operator=(const Deque &t) {
        clear();
        Elem *tmp = t.Front;
        for(int i = 0; i < Count; ++i){
            push_back(tmp);
            tmp = tmp->Next;
        }
    }*/

    Deque &operator=(const Deque &t) {
        if (&t==this)
            return *this;
        clear();
        Elem *tmp = t.Front;
        for(size_type i = 0; i < Count; ++i){
            push_back(tmp->Value);
            tmp = tmp->Next;
        }
        return *this;
    }

    Deque(const Deque &t) {
        Elem *tmp = t.Front;
        for(size_type i = 0; i < Count; ++i){
            push_back(tmp->Value);
            tmp = tmp->Next;
        }
    }

    /*Deque(const Deque &t) {
        Elem *tmp = t.Front;
        for(int i = 0; i < Count; ++i){
            push_back(tmp);
            tmp = tmp->Next;
        }
    }*/

    ~Deque() {
        Elem *delete_Elem = Front;
        for (Elem *p = Front; p != Rear;)
        {
            p = p->Next;
            delete delete_Elem;
            --Count;
            delete_Elem = p;
        }
        delete delete_Elem;
    }

    bool empty() const
    {
        bool t = (Front == Rear);
        return t;
    }

    size_type size() const {
        return Count;
    }

    reference front() {
        if (empty())
            throw new DequeEmptyException();

        return Front->Value;
    }

    reference back() {
        if (empty())
            throw new DequeEmptyException();

        return Rear->Prev->Value;
    }


    Iterator begin() {
        return ffront;
    }

    Iterator end() {
        return rear;
    }

    void push_front(const value_type &a) {
        Elem *p = new Elem(a);
        p->Next = Front;
        p->Prev = 0;
        Front->Prev = p;
        Front = p;
        ffront = Iterator(Front);
        ++Count;
    }

    void push_back(const value_type &a) {
        if (empty()) push_front(a);
        else {
            Elem *p = new Elem(a);
            p->Next = Rear;
            p->Prev = Rear->Prev;
            Rear->Prev->Next = p;
            Rear->Prev = p;
            ++Count;
        }
    }

    void pop_front() {
        if (!empty()) {
            Elem *p = Front;
            Front = Front->Next;
            Front->Prev = 0;
            ffront = Iterator(Front);
            --Count;
        }

    }

    void pop_back() {
        if (!empty()) {
            Elem *p = Rear->Prev;
            if (p == nullptr) pop_front();
            else {
                Rear->Prev= nullptr;
                Rear=p;
                p->Next = nullptr;
                --Count;
            }

        }

    }

    void clear() {
        Elem *tmp;
        while (Front != nullptr) {
            tmp = Front;
            Front = Front->Next;
            delete tmp;
        }
    }


    reference at(size_type index) const {
        if (index < 0 || index >= Count)
            throw std::out_of_range("Check the index!\n");
        Elem *tmp = Front;
        for (int i = 0; i < Count - 1; i++) {
            tmp = tmp->Next;
        }
        return tmp->Value;
    }


    reference operator[](size_type index) {
        Elem *tmp = Front;
        for (int i = 0; i < Count - 1; i++) {
            tmp = tmp->Next;
        }
        return tmp->Value;
    }

    const_reference operator[](size_type index) const {
        Elem *tmp = Front;
        for (int i = 0; i < Count - 1; i++) {
            tmp = tmp->Next;
        }
        return tmp->Value;
    }

    void swap(Deque& other)
    {
        std::swap(Count, other.Count);
        std::swap(Front, other.Front);
        std::swap(Rear, other.Rear);
        std::swap(ffront, other.ffront);
        std::swap(rear, other.rear);
    }

private:
    class Elem {
    public:
        Elem(const value_type &a) : Value(a) {}

        Elem(const Elem &t) {
            Next=NULL;
            Prev=NULL;
            Value=t.Value;
        }

        Elem() {}

        ~Elem() {}
        value_type Value;
        Elem *Next;
        Elem *Prev;
    };


    size_type Count;
    Elem *Front;
    Elem *Rear;
    Iterator ffront;
    Iterator rear;

};


#endif //DEQUE_TDEQUE_H
