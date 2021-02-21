#include <iostream>

template<typename T>
struct Node
{
    Node<T>* next;
    T data;

    Node();
    Node(T data, Node<T>* next);
};

template<typename T>
class List
{
private:
    int count;
    Node<T>* head;

public:
    List();

};

template<typename T>
Node<T>::Node()
{
        next = nullptr;
}

template<typename T>
Node<T>::Node(T data, Node<T>* next)
{
        this->data = data;
        this->next = next;
}

template<typename T>
List<T>::List()
{
    head = nullptr;
    count = 0;
}

int main()
{
    List<int> numbers;

    return 0;
}
