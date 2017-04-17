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

    // создаем дек с единственным элементом
    Deque(const value_type &a) : Front(new Elem()), Rear(Front), Count(0) {
        Rear->Next = Rear->Prev = 0;
        ffront = Iterator(Front);
        rear = Iterator(Rear);
        push_front(a);
    }

    ~Deque() {
        Elem *delete_Elem = Front;           // удаляемый элемент
        for (Elem *p = Front; p != Rear;)       // Пока не уперлись в запредельный
        {
            p = p->Next;                      // подготовили следующий
            delete delete_Elem;
            --Count;      // удалили элемент
            delete_Elem = p;                  // подготовили для удаления
        }
        delete delete_Elem;
    }

    bool isEmpty() const                    // есть ли элементы в деке
    {
        bool t = (Front == Rear);
        return t;
    }

    size_type size() const {
        return Count;
    }

    reference front() {
        if (isEmpty())
            throw new DequeEmptyException();

        return Front->Value;
    }

    reference back() {
        if (isEmpty())
            throw new DequeEmptyException();

        return Rear->Value;
    }

    // методы доступа
    Iterator begin() {
        return ffront;
    }

    Iterator end() {
        return rear;
    }

    void push_front(const value_type &a) {
        Elem *p = new Elem(a);          // образовали новый элемент
        p->Next = Front;
        p->Prev = 0;    // "привязали"
        Front->Prev = p;
        Front = p;       // первым в деке
        ffront = Iterator(Front);
        ++Count;
    }

    void push_back(const value_type &a) {
        if (isEmpty()) push_front(a);
        else {
            Elem *p = new Elem(a);
            p->Next = Rear;
            p->Prev = Rear->Prev;
            Rear->Prev->Next = p;
            Rear->Prev = p;
        }
        ++Count;
    }

    void pop_front() {
        if (!isEmpty()) {
            Elem *p = Front;
            Front = Front->Next;
            Front->Prev = 0;
            ffront = Iterator(Front);
            --Count;
            delete p;
        }

    }

    void pop_back() {
        if (!isEmpty()) {
            Elem *p = Rear->Prev;
            if (p == 0) pop_front();
            else {
                p->Prev->Next = Rear;
                Rear->Prev = p->Prev;
                delete p;
            }
            --Count;
        }

    }

    void clear() {
        Elem *tmp;
        while (Front != nullptr) {
            tmp = Front;
            Front = Front->Next;//переходим к след
            delete tmp;// удаляем предыдущий
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

private:
    class Elem {
    public:
        Elem(const value_type &a) : Value(a) {}

        Elem() {}

        ~Elem() {}               // объявлять необязательно
        value_type Value;            // информационная часть элемента
        Elem *Next;             // следующий элемент
        Elem *Prev;             // предыдущий элемент
    };

    Deque &operator=(const Deque &) {}

    Deque(const Deque &) {}

    value_type Count;
    Elem *Front;
    Elem *Rear;
    Iterator ffront;
    Iterator rear;

};


#endif //DEQUE_TDEQUE_H
