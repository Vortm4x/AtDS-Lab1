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
    Node<T>* initChain(Node<T>* node);

public:
    List();
    List(const List<T>& list);
    ~List();
    int length();
    bool isFull();
    bool isEmpty();
    void operator=(const List<T>& list);
    T operator[](const int& index);
	void print();
	void insert(const T& data);
    T pop_front();
	T pop_back();
	int remove(const T& data);
	bool search(const T& data);
	void clear();

	T sum();
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

// ----------------------------
//  bool List<T>::isEmpty()
//  Checks the nodes existance
// ----------------------------
template<typename T>
bool List<T>::isEmpty()
{
    return (head == nullptr);
}

// ---------------------------------------------
//  void List<T>::operator=(const List<T>& list)
//  Assigning operator
// ---------------------------------------------
template<typename T>
void List<T>::operator=(const List<T>& list)
{
    this->clear();
    count = list.count;
    head = initChain(list.head);
}

// -----------------------------------------
//  T List<T>::operator[](const int& index)
//  List indexation
// -----------------------------------------
template<typename T>
T List<T>::operator[](const int& index)
{
    Node<T>* current = head;

    for(int i(0); i < index; ++i)
    {
        current = current->next;
    }

    return current->data;
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

// ---------------------------------------
//  T List<T>::pop_back()
//	Deletes the node at the end of list
// ---------------------------------------
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

// --------------------------------------------------
//  void List<T>::remove()
//	Removes all found values as in arguments,
//  if there are no, does nothing; returns deletions
// --------------------------------------------------
template<typename T>
int List<T>::remove(const T & data)
{
    int deletions = 0;

	if(!isEmpty())
	{
		Node<T>* previous = nullptr;
		Node<T>* current = head;

		while(current != nullptr)
        {
            if(current->data == data)
            {
                break;
            }

            previous = current;
            current = current->next;
        }

        if(previous == nullptr)
        {
            while( (head != nullptr) && (head->data == data) )
            {
                previous = head;
                head = head->next;
                delete previous;
                ++deletions;
            }
        }
        else
        {
            while( (current != nullptr) && (current->data == data) )
            {
                previous = current;
                current = current->next;
                delete previous;
                ++deletions;
            }
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

        current = current->next;
    }

    return false;
}

// -----------------------
//  void List<T>::print()
//	  Prints the list
// -----------------------
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

// ------------------------------------
//  void List<T>::insert(const T& data)
//	Inserts a value on its place
// ------------------------------------
template<typename T>
void List<T>::insert(const T& data)
{
    Node<T>* previous = nullptr;
    Node<T>* current = head;

    while(current != nullptr)
    {
        if(data < current->data)
        {
            break;
        }

        previous = current;
        current = current->next;
    }

    if(previous == nullptr)
    {
        head = new Node<T>(data, head);
    }
    else
    {
        previous->next = new Node<T>(data, previous->next);
    }

    ++count;
}

// -----------------------
//  void List<T>::clear()
//	Clears the list
// -----------------------
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

template<typename T>
T List<T>::sum()
{
    T value = T();
    Node<T>* current = head;

    while(current != nullptr)
    {
        value += current->data;
        current = current->next;
    }

    return value;
}

void testCopy(List<int> list)
{
    list.insert(104);
    list.print();
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

    numbers.insert(5);
    numbers.print();

    std::cout << numbers.search(10) << " " <<numbers.search(0) << std::endl;

    std::cout << numbers[0] << ' ' << numbers[3] << std::endl;
    std::cout << numbers[0] << ' ' << numbers[3] << std::endl;

    List<int> same;

    for(int i = 0; i < 8; ++i)
    {
        same.insert(3);
    }

    same.print();


    std::cout << same.remove(2) << ' ' << same.remove(3) << ' ' << same.remove(2) << std::endl;

    testCopy(numbers);
    numbers.print();

    same = numbers;
    same.print();

    std::cout << same.sum() << std::endl;

    return 0;
}
