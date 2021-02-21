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
    int count;
    Node<T>* head;

public:
    List();
    ~List();
    int length();
    bool isFull();
    bool isEmpty();
    void addNode(T data);
    T deleteNode(T data);
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
    count = 0;
    head = nullptr;
}

// ----------------------------
//  List<T>::~List()
//  Default list destructor
// ----------------------------
template<typename T>
List<T>::~List()
{
    count = 0;
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
    return count;
}


// ------------------------------
//  bool List<T>::isFull()
//  Checks memory overflow
// -----------------------------
template<typename T>
bool List<T>::isFull()
{
    Node<T>* test = new Node<T>();
    bool result = (test == nullptr);
    delete test;
    return result;
}

// ---------------------------------
//  bool List<T>::isEmpty()
//  Checks the nodes existance
// ---------------------------------
template<typename T>
bool List<T>::isEmpty()
{
    return (head == nullptr);
}

// -------------------------------
//  void List<T>::addNode(T data)
//  Adds a new node to head
// -------------------------------
template<typename T>
void List<T>::addNode(T data)
{
    if(!isFull())
    {
        head = new Node<T>(data, head);
        ++count;
    }
    else
    {
        std::cout << "List overflow\n";
    }
}

// ------------------------------
//  T List<T>deleteNode(T data);
//  Deletes a first found
//  node with same value
// -----------------------------
template<typename T>
T List<T>::deleteNode(T data)
{
    //Empty list
    if(isEmpty())
    {
        std::cout << "List underflow\n";
        return 0x3f3f3f3f;
    }

    Node<T>* previous = nullptr;
    Node<T>* following = head;

    while((following != nullptr) && (following->data != data))
    {
        previous = following;
        following = following->next;
    }
    int result = 0;

    //Node is the head
    if((previous == nullptr) && (following != nullptr) && (following->data == data))
    {
        result = following->data;
        head = head->next;
        delete following;
        --count;
        return result;
    }//Node is not head
    else if((previous !=
             nullptr) && (following != nullptr) && (following->data== data))
    {
        result = following->data;
        previous->next = following-> next;
        delete following;
        --count;
        return result;
    }
    else
    {
        std::cout << "Item wasn't found and not deleted";
        return 0x3f3f3f3f;
    }
}

int main()
{
    List<int> numbers;
    for(int i = 0; i < 6; ++i)
    {
        numbers.addNode(i);
    }

    std::cout << numbers.deleteNode(12);
    std::cout << numbers.deleteNode(4);

    return 0;
}
