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
	std::function<bool(const T& a, const T& b)> compare;

public:
    List(std::function<bool(const T& a, const T& b)> compare = [](const T& a, const T& b){ return a < b; } );
    ~List();
    int length();
    bool isFull();
    bool isEmpty();
	void print();
	void insert(const T& data);
    T pop_front();
	T pop_back();
	int remove(const T& data);
	void clear();
	void resort(std::function<bool(const T& a, const T& b)> compare);
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
List<T>::List(std::function<bool(const T& a, const T& b)> compare)
{
    this->compare = compare;
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

// ----------------------------------
//  void List<T>::insert(const T& data)
//	Inserts a value on its place
// ----------------------------------
template<typename T>
void List<T>::insert(const T& data)
{
    Node<T>* current = head;
    Node<T>* place = nullptr;

    bool isReversed = false;

    if(count > 1)
    {
        if(compare(head->next->data, head->data))
        {
            isReversed = true;
        }
    }

    while(current != nullptr)
    {
        bool cmp = compare(data, current->data);

        if(isReversed)
        {
            cmp = !cmp;
        }

        if(cmp)
        {
            break;
        }
        else
        {
            place = current;
            current = current->next;
        }
    }

    if(place == nullptr)
    {
        head = new Node<T>(data, head);
    }
    else
    {
        place->next = new Node<T>(data, place->next);
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
//  void List<T>::resort()
//	  Sorts the list [O(N^2)]
// -----------------------------
template<typename T>
void List<T>::resort(std::function<bool(const T& a, const T& b)>compare)
{
    this->compare = compare;

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

int main()
{
    List<int> numbers;

    for(int i = 0; i < 5; ++i)
    {
        numbers.insert(i * 2);
    }

    numbers.print();

    numbers.insert(3);
    numbers.print();

    numbers.resort([](const int& a, const int& b){return a > b; });
    numbers.print();

    numbers.insert(5);
    numbers.print();

    std::cout << "compiled\n";

    return 0;
}
