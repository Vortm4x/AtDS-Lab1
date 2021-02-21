#include <iostream>

// -----------------------------------------
//  struct Node<T>
//  Consists data and ptr on next node
// -----------------------------------------
template<typename T>
struct Node
{
    Node<T>* next;
    T data;

    Node();
    Node(T data, Node<T>* next);
};

// -------------------------------------------
//  class List<T>
//  Consists  a quantity of nodes and
//  and a ptr on the next one + methods
// -------------------------------------------
template<typename T>
class List
{
private:
    int length;
    Node<T>* head;

public:
    List();
    ~List();
    int length();
    void add(T data);
};

// -------------------------------
//  Node<T>::Node()
//  Default node constructor
// -------------------------------
template<typename T>
Node<T>::Node()
{
        next = nullptr;
}

// -----------------------------------------------
//  Node<T>::Node(T data, Node<T>* next)
//  Node constructor  with params
// -----------------------------------------------
template<typename T>
Node<T>::Node(T data, Node<T>* next)
{
        this->data = data;
        this->next = next;
}

// -----------------------------
//  List<T>::List()
//  Default list constructor
// -----------------------------
template<typename T>
List<T>::List()
{
    head = nullptr;
    length = 0;
}

// ----------------------------
//  List<T>::~List()
//  Default list destructor
// ----------------------------
template<typename T>
List<T>::~List()
{
    length = 0;
    Node<T>* current;

    while(head != nullptr)
    {
        current = head;
        head = head->next;
        delete current;
    }
}

// -------------------------
//  int List<T>::length()
//  Returns a list length
// -------------------------
template<typename T>
int List<T>::length()
{
    return length;
}

// -------------------------
//  void List<T>::add(T data)
//
// -------------------------
template<typename T>
void List<T>::add(T data)
{

}

int main()
{
    List<int> numbers;

    return 0;
}
