#include <iostream>

template<typename T>
struct Node
{
    Node<T>* next;
    T data;

    Node();
    Node(T data, Node<T>* next);
};
/*
class List
{
private:
    int count;
    Node<T>* head;

public:
    List();

};

*/

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

int main()
{
    Node<int>* node = new Node<int>(5, nullptr);
    std::cout << node->data;


    return 0;
}
