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

	Node(const T& data = T(), Node<T> *const next = nullptr);
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
	void print();
    void unshift(const T& data);
	void push_back(const T& data);
	T pop_back();
};

// -----------------------------------------------
//  Node<T>::Node(T data, Node<T>* next)
//  Node constructor  with default params
// -----------------------------------------------
template<typename T>
Node<T>::Node(const T& data, Node<T> *const next)
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

// -----------------------------------------------
//  void List<T>::unshift(const T& data)
//  Puts the node on the begin of list
// ----------------------------------------------
template<typename T>
void List<T>::unshift(const T& data)
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

// ---------------------------------------------
//  void List<T>::push_back(const T& data)
//	  Puts the node to the end of list
// --------------------------------------------
template<typename T>
void List<T>::push_back(const T& data)
{
	if (!isFull())
	{
		if(!isEmpty())
		{
			Node<T>* end = head;

			while (end->next != nullptr)
			{
				end = end->next;
			}

			end->next = new Node<T>(data);
		}
		else
		{
			head = new Node<T>(data);
		}
		++count;
	}
	else
	{
		std::cout << "List overflow\n";
	}
}

// ---------------------------------------------
//  T List<T>::pop_back()
//	  Deletes the node at the end of list
// --------------------------------------------
template<typename T>
T List<T>::pop_back()
{
	if (!isEmpty())
	{
		Node<T>* end = head;
		Node<T>* current = nullptr;

		while(end->next != nullptr)
		{
			current = end;
			end = end->next;
		}

		(current == nullptr) ? head = nullptr : current->next = nullptr;

		T data = end->data;
		delete end;
		--count;

		return data;
	}
	else
	{
		return T();
	}
}

// --------------------------
//  void List<T>::print()
//	  Prints the list
// -------------------------
template<typename T>
void List<T>::print()
{
	if (!isEmpty())
	{
		Node<T>* current = head;

		while (current != nullptr)
		{
			std::cout << current->data << ", ";
			current = current->next;
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "<EMPTY>\n";
	}
}

int main()
{
    List<int> numbers;
   
	for (int i(0); i < 6; ++i)
	{
		numbers.push_back(i);
	}

	numbers.print();
	std::cout << numbers.pop_back() << '\n';
	numbers.print();


    return 0;
}
