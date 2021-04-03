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
	void swap(Node<T>* a, Node<T>* b);
	Node<T>* initChain(Node<T>* node);

public:
    List();
    List<T>(const List<T>& list);
    ~List();
    int length();
    bool isFull();
    bool isEmpty();
    T& operator[](const int& index);
	void print();
    void push_front(const T& data);
	T pop_front();
	void push_back(const T& data);
	T pop_back();
	int remove(const T& data);
	bool search(const T& data);
	void clear();
	void sort();
	void reverse();
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

// -----------------------------------
//  List<T>::List(сonst List<T>& list)
//  Copying list constructor
// -----------------------------------
template<typename T>
List<T>::List(const List<T>& list)
{
    count = list.count;
    head = initChain(list.head);
}

// --------------------------------------------
//  Node<T>* List<T>::initChain(Node<T>* node)
//  Recursivly creates the same "sublist" as a
//  parameter one from node to end
// --------------------------------------------
template<typename T>
Node<T>* List<T>::initChain(Node<T>* node)
{
    return (node == nullptr) ? nullptr : new Node<T>(node->data, initChain(node->next));
}

// ----------------------------
//  List<T>::~List()
//  Default list destructor
// ----------------------------
template<typename T>
List<T>::~List()
{
	clear();
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
//  T List<T>::operator[](const int& index)
//  List indexation
// -----------------------------------------
template<typename T>
T& List<T>::operator[](const int& index)
{
    Node<T>* current = head;

    for(int i(0); i < index; ++i)
    {
        current = current->next;
    }

    return current->data;
}

// -----------------------------------------------
//  void List<T>::push_front(const T& data)
//  Puts the node on the begin of list
// ----------------------------------------------
template<typename T>
void List<T>::push_front(const T& data)
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

// -----------------------------------------------
//  T List<T>::pop_front()
//  Deletes the node on the begin of list
// ----------------------------------------------
template<typename T>
T List<T>::pop_front()
{
	if (!isEmpty())
	{
		Node<T>* temp = head;
		head = head->next;

		T data = temp->data;
		delete temp;
		--count;

		return data;
	}
	else
	{
		return T();
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
//	Deletes the node at the end of list
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

// ----------------------------------------------------
//  void List<T>::remove()
//	Removes all found values as in arguments,
//  if there are no, does nothing; returns size
// ----------------------------------------------------
template<typename T>
int List<T>::remove(const T & data)
{
	int deletions(0);

	Node<T>* previous = nullptr;
	Node<T>* current = head;

	while(current != nullptr)
    {
        if(current->data == data)
        {
            if(previous == nullptr)
            {
                head = head->next;
                delete current;
                current = head;
            }
            else
            {
                previous->next = current->next;
                delete current;
                current = previous->next;
            }
            ++deletions;
        }
    }

    count -= deletions;
	return deletions;
}


// ------------------------------------
//  bool List<T>::search(const T& data)
//	Checks is available searching data
// ------------------------------------
template<typename T>
bool List<T>::search(const T& data)
{
    Node<T>* current = head;

    while(current != nullptr)
    {
        if(data == current->data)
        {
            return true;
        }
        else
        {
            current = current->next;
        }
    }

    return false;
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

// --------------------------
//  void List<T>::clear()
//	  Clears the list
// -------------------------
template<typename T>
void List<T>::clear()
{
	count = 0;
	Node<T>* current;

	while (head != nullptr)
	{
		current = head;
		head = head->next;
		delete current;
	}
}

// ---------------------------------------------------------
//  void List<T>::swap(Node<T>* a, Node<T>* b)
//	  Swaps values of two nodes
// ---------------------------------------------------------
template<typename T>
void List<T>::swap(Node<T>* a, Node<T>* b)
{
	T temp = a->data;
	a->data = b->data;
	b->data = temp;
}

// -----------------------------
//  void List<T>::sort()
//	  Sorts the list [O(N^2)]
// -----------------------------
template<typename T>
void List<T>::sort()
{
	if (!isEmpty())
	{
		Node<T>* current = head;
		Node<T>* comparing = nullptr;
		Node<T>* min = nullptr;

		while(current != nullptr)
		{
			comparing = current;
			min = current;

			do
			{
				if (comparing->data < min->data)
				{
					min = comparing;
				}
				comparing = comparing->next;
			}
			while (comparing != nullptr);

			swap(min, current);
			current = current->next;
		}
	}
}


// -----------------------------
//  void List<T>::reverse()
//	  Reverses the list
// -----------------------------
template<typename T>
void List<T>::reverse()
{
	Node<T>* current = head;
	Node<T>* previous = nullptr;
	Node<T>* following = nullptr;

	while (current != nullptr)
	{
		following = current->next;
		current->next = previous;
		previous = current;
		current = following;
	}

	head = previous;
}

void testCopy(List<int> list)
{
    list.push_back(104);
    list.print();
}

int main()
{
    List<int> numbers;

	numbers.push_front(2);
	numbers.push_front(9);
	numbers.push_front(7);
	numbers.push_front(4);
	numbers.push_front(8);
	numbers.push_front(3);
	numbers.push_front(1);
	numbers.push_front(5);
	numbers.push_front(6);
	numbers.print();

	numbers.sort();
	numbers.print();

	numbers.reverse();
	numbers.print();

	numbers[0] = 1000;
	numbers.print();

	testCopy(numbers);
	numbers.print();

	std::cout << numbers.search(11) << "  " << numbers.search(1) << std::endl;

    return 0;
}
