
/* Name: Andrew Stade
Date: 10/8/2020
Section: COP 4530 */

// Member functions of nested const_iterator class:
template <class T>
List<T>::const_iterator::const_iterator()	// default zero-parameter constructor. Set pointer current to nullptr.
{
	current = nullptr;		// from ch3 slides.
}

template <class T>
const T & List<T>::const_iterator::operator*() const	// returns a reference to the corresponding element in the list by calling retrieve() member function.
{
	return retrieve();		// from ch3 slides.
}

template <class T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++()	// prefix and postfix increment and decrement operators.
{
	current = current->next;	// from ch3 slides.
	return(*this);
}

template <class T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
	const_iterator old = *this;		// from ch3 slides.
	++(*this); 		// +1. seg fault (?)
	return old;
}

template <class T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--()
{
	current = current->prev;	// from ch3 slides.
	return(*this);
}

template <class T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
	const_iterator old = *this;		// from ch3 slides.
	--(*this); // -1. seg fault (?)
	return old;
}

template <class T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const	// two iterators are equal if they refer to the same element.
{
	return(current == rhs.current);		// from ch3 slides.
}

template <class T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const
{
	return(current != rhs.current);		// from ch3 slides.
}

template <class T>
T & List<T>::const_iterator::retrieve() const	// return a reference to the corresponding element in the list.
{
	return(current->data);		// from ch3 slides.
}

template <class T>
List<T>::const_iterator::const_iterator(Node * p)	// one-parameter constructor. Set pointer current to the given node pointer p.
{
	current = p;		// from ch3 slides.
}

// Member functions of nested iterator class:
template <class T>
List<T>::iterator::iterator()	// default zero-parameter constructor.
{
	init();	
}

template <class T>
T & List<T>::iterator::operator*()	// returns a reference to the corresponding element in the list by calling retrieve() member function.
{
	return(const_iterator::retrieve());		// from ch3 slides.
}

template <class T>
const T & List<T>::iterator::operator*() const
{
	return(const_iterator::operator*());	// from ch3 slides.
}

template <class T>
typename List<T>::iterator & List<T>::iterator::operator++()	// prefix and postfix increment and decrement operators.
{
	this->current = this->current->next;	// from ch3 slides.
	return(*this);
}

template <class T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
	iterator old = *this;	// from ch3 slides.
	++(*this);
	return old;
}

template <class T>
typename List<T>::iterator & List<T>::iterator::operator--()
{
	this->current = this->current->prev;	// from ch3 slides.
	return(*this);
}

template <class T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
	iterator old = *this;	// from ch3 slides.
	--(*this);
	return old;
}

template <class T>
List<T>::iterator::iterator(Node * p)	// one-parameter constructor.
{
	this->current = p;	
}

// Member functions of List class template
template <class T>
List<T>::List()		// Default zero-parameter constructor. Call init() to initialize list member variables.
{
	init();
}

template <class T>
List<T>::List(const List &rhs)	// Copy constructor. Create the new list using elements in existing list rhs.
{
	init();
	auto itr = rhs.begin();
	
	for(int i = 0; i < rhs.size(); i++)
	{
		push_back(*itr);
		itr++;
	}
}

template <class T>
List<T>::List(List && rhs)	// move constructor.
{
	theSize = rhs.theSize;
	head = rhs.head;
	tail = rhs.tail;

	rhs.theSize = 0;
	rhs.head = nullptr;
	rhs.tail = nullptr;
}

template <class T>
List<T>::List(int num, const T& val)	// Construct a list with num elements, all initialized with value val.
{
	init();
	
	for(int i = 0; i < num; i++)
	{
		push_back(val);
	}
}

template <class T>
List<T>::List(const_iterator start, const_iterator end)		// construct a List with elements from another list between start and end.
{
	init();
	auto itr = start;
	
	while(itr != end)
	{
		push_back(*itr);
		itr++;
	}
}

template <class T>
List<T>::List(std::initializer_list<T> iList)	// construct a List with elements from the initializer list that is passed in.
{
	init();
	
	for(T i : iList)
	{
		push_back(i);
	}
}

template <class T>
List<T>::~List() 	// destructor. You should properly reclaim all dynamically allocated memory
{
	if(empty() == false)	// from ch3 slides.
	{
		clear(); 	// if data exists, clear it.
	}
	
	delete head;
	delete tail;
}

template <class T>
const List<T>& List<T>::operator=(const List &rhs)	// copy assignment operator
{
	clear();
	auto itr = rhs.begin();
	
	for(int i = 0; i < rhs.size(); i++)		// from ch3 slides.
	{
		push_back(itr.retrieve());
		itr++;
	}
	
	return *this;
}

template <class T>
List<T> & List<T>::operator=(List && rhs)	// move assignment operator
{
	std::swap(theSize, rhs.theSize);
	std::swap(head, rhs.head);
	std::swap(tail, rhs.tail);
}

template <class T>
List<T>& List<T>::operator=(std::initializer_list<T> iList) // assign the initializer list data to be the calling object's new data
{
	init();
	
	for(T i : iList)
	{
		push_back(i);
	}
}

template <class T>
int List<T>::size() const	// return the number of elements in the List.
{
	return theSize;
}

template <class T>
bool List<T>::empty() const		// return true if no element is in the list; otherwise, return false.
{
	if(theSize == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
void List<T>::clear()		// delete all the elements in the list
{
	auto itr = begin();
	
	while(itr.current != tail)
	{
		itr = erase(itr);
	}
}

template <class T>
void List<T>::reverse()		// reverse the order of the elements in the list.
{
	auto itr = end();
	List<T> newlist;
	itr--;
	
	for(int i = 0; i < theSize; i++)
	{
		newlist.push_back(*itr);
		itr--;
	}
	*this = newlist;
}

template <class T>
T& List<T>::front() 	// return reference to the first and last element in the list, respectively.
{
	return(head->next->data);
}

template <class T>
const T& List<T>::front() const
{
	return(head->next->data);
}

template <class T>
T& List<T>::back()
{
	return(tail->prev->data);
}

template <class T>
const T& List<T>::back() const
{
	return(tail->prev->data);
}

template <class T>
void List<T>::push_front(const T& val)	// insert the new object as the first and last element into the list, respectively; and their move versions.
{
	insert(begin(), val);
}

template <class T>
void List<T>::push_front(T && val)
{
	insert(begin(), std::move(val));
}

template <class T>
void List<T>::push_back(const T & val)
{
	insert(end(), val);
}

template <class T>
void List<T>::push_back(T && val)
{
	insert(end(), std::move(val));
}

template <class T>
void List<T>::pop_front()		// delete the first and last element in the list, respectively.
{
	erase(begin());
}

template <class T>
void List<T>::pop_back()
{
	erase(end().current->prev);
}

template <class T>
void List<T>::remove(const T &val)	// delete all nodes with value equal to val from the list.
{
	auto itr = begin();
	
	while(itr != end())
	{
		if(itr.retrieve() == val)
		{
			itr = erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

template <class T>
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred)		// delete all nodes for which pred returns true.
{
	auto itr = begin();
	
	while(itr != end())
	{
		if(pred(*itr) == true)
		{
			itr = erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

template <class T>
void List<T>::print(std::ostream& os, char ofc) const	// print all elements in the list, using character ofc as the deliminator between elements in the list.
{
	const_iterator itr = begin();
	
	for(int i = 0; i < theSize - 1; i++)
	{
		os << itr.retrieve() << ofc;
		itr++;
	}
	os << itr.retrieve();
}

template <class T>
typename List<T>::iterator List<T>::begin()		// return iterator to the first element in the list.
{
	return iterator(head->next);
}

template <class T>
typename List<T>::const_iterator List<T>::begin() const
{
	return const_iterator(head->next);
}

template <class T>
typename List<T>::iterator List<T>::end()		// return iterator to the end marker of the list (tail).
{
	return iterator(tail);
}

template <class T>
typename List<T>::const_iterator List<T>::end() const
{
	return const_iterator(tail);
}

template <class T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val)	// insert value val ahead of the node referred to by itr; and its move version
{
	Node *p = itr.current;
	++theSize;
	return iterator(p->prev = p->prev->next = new Node{val, p ->prev, p});
}

template <class T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val)
{
	Node *p = itr.current;
	++theSize;
	return iterator(p->prev = p->prev->next = new Node{val, p ->prev, p});
}

template <class T>
typename List<T>::iterator List<T>::erase(iterator itr)		// delete node referred to by itr. The return value is an iterator to the following node.
{
	Node *p = itr.current;
	iterator retVal(p->next);
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	theSize--;
	
	return retVal;
}

template <class T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end)	// delete all nodes between start and end (including start but not end), that is, all elements in the range [start, end).
{
	iterator itr = start;
	
	for(int i = 0; i < theSize - 1; i++)
	{
		itr = erase(itr);
	}
}

template <class T>
void List<T>::init()	// initialize the member variables of list.
{
	theSize = 0;
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->prev = head;
}

// Non-class functions
template <class T>
bool operator==(const List<T> &lhs, const List<T> &rhs)	// check if two lists contain the same sequence of elements.
{
	auto itrlhs = lhs.begin();
	auto itrrhs = rhs.begin();
	
	if (lhs.size() != rhs.size())
	{
		return false;
	}
	
	while(itrlhs != lhs.end())
	{
		if(*itrlhs != *itrrhs)
		{
			return false;
		}
		++itrlhs;
		++itrrhs;
	}
	
	return true;
}

template <class T>
bool operator!=(const List<T> &lhs, const List<T> &rhs)	// opposite of operator==().
{
	return !(lhs == rhs);
}

template <class T>
std::ostream & operator<<(std::ostream &os, const List<T> &l)	// print out all elements in list l by calling List<T>::print() function. 
{
	l.print(os);
}


