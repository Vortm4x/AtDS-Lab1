#include <iostream>
#include <functional>

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

public:
    List();
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
	bool search(const T& data, std::function<bool(const T& a, const T& b)> equal= [](const T& a, const T& b) {return a < b;} );
	void clear();
	void sort(std::function<bool(const T& a, const T& b)> compare = [](const T& a, const T& b) {return a < b;} );
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

// ----------------------------------------------------
//  void List<T>::remove()
//	  Removes all found values as in arguments,
//  if there are no, does nothing; returns size
// ----------------------------------------------------
template<typename T>
int List<T>::remove(const T & data)
{
	if(!isEmpty())
	{
		Node<T>* previous = nullptr;
		Node<T>* current = head;

		do
		{
			if (current->data == data)
			{
				if (previous == nullptr)
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

				--count;
			}
			else
			{
				previous = current;
				current = current->next;
			}
		} while (current != nullptr);
	}

	return count;
}


// ------------------------------------
//  bool List<T>::search(const T& data)
//	Checks is available searching data
// ------------------------------------
template<typename T>
bool List<T>::search(const T& data, std::function<bool(const T& a, const T& b)> equal)
{
    Node<T>* current = head;

    while(current != nullptr)
    {
        if(equal(data, current->data))
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
void List<T>::sort(std::function<bool(const T& a, const T& b)>compare)
{
	if (!isEmpty())
	{
		Node<T>* current = head;
		Node<T>* comparing = nullptr;
		Node<T>* extremum = nullptr;

		while(current != nullptr)
		{
			comparing = current;
			extremum = current;

			do
			{
				if (compare(comparing->data, extremum->data))
				{
					extremum = comparing;
				}
				comparing = comparing->next;
			}
			while (comparing != nullptr);

			swap(extremum, current);
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

	numbers.sort([](int a, int b) {return a > b; });
	numbers.print();

	numbers.reverse();
	numbers.print();

	numbers[0] = 1000;
	numbers.print();

	std::cout << numbers.search(11) << "  " << numbers.search(1) << std::endl;

    return 0;
}
