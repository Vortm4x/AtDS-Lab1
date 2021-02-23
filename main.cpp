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

	Node(T data = T(), Node<T>* next = nullptr);
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
    void addFirst(const T& data);
	void addLast(const T& data);
};

// -----------------------------------------------
//  Node<T>::Node(T data, Node<T>* next)
//  Node constructor  with default params
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

// -----------------------------------------
//  void List<T>::addFirst(const T& data)
//  Puts the node on the begin of list
// -----------------------------------------
template<typename T>
void List<T>::addFirst(const T& data)
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


// ---------------------------------------
//  void List<T>::addLast(const T& data)
//	  Puts the node to the end of list
// ---------------------------------------
template<typename T>
void List<T>::addLast(const T& data)
{
	if (!isFull())
	{
		Node<T>* end = head;

		if(!isEmpty)
		{
			while (end->next != nullptr)
			{
				end = end->next;
			}
		}

		end->next = new Node(data);
		++count;
	}
	else
	{
		std::cout << "List overflow\n";
	}
}

int main()
{
    List<int> numbers;
   
	for (int i(0); i < 6; ++i)
	{
		numbers.addFirst(i);
	}

    return 0;
}
