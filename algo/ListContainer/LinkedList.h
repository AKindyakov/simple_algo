#include <cstdlib>

class IListNode 
{
public:
    IListNode(){};
    virtual ~IListNode(){};
};


template<class Item> 
class LinkedListNode : public IListNode 
{
public:
    LinkedListNode();
    LinkedListNode(Item*, LinkedListNode<Item>*);
    virtual ~LinkedListNode();
    
    LinkedListNode* next;
    Item* item;
};

template<class T>
class LinkedList
{
public:
    LinkedList();
    LinkedList(int size);
    virtual ~LinkedList();
   
    void push_front(T); 
    void push_front(T*); 
    void pop_front(); 
    
    void erase(LinkedListNode<T>* begin, LinkedListNode<T>* end); 
    
    T* getBegin()
    {
        return start; 
    }; 
    
private:
    LinkedListNode<T>* start;
};

template<class Item> 
class DublyLinkedListNode : public IListNode 
{
public:
    DublyLinkedListNode(){};
    ~DublyLinkedListNode(){};
    
    DublyLinkedListNode* next;
    Item* item;
};


template<class T>
class DublyLinkedList
{
public:
    DublyLinkedList(){};
    ~DublyLinkedList(){};
    
    DublyLinkedListNode<T>* getNode(); 
private:
    DublyLinkedListNode<T>* start;
    DublyLinkedListNode<T>* end;
};

template<class Item> 
LinkedListNode<Item>::LinkedListNode()
    : item(NULL), next(NULL) 
{}

template<class Item> 
LinkedListNode<Item>::LinkedListNode(Item* _pItem, LinkedListNode<Item>* _pNode)
    : item(_pItem), next(_pNode) 
{}

template<class Item> 
LinkedListNode<Item>::~LinkedListNode()
{
    
}

template<class T>
LinkedList<T>::LinkedList()
    : start(new LinkedListNode<T>())
{}

template<class T>
LinkedList<T>::LinkedList(int n)
    : start(new LinkedListNode<T>())
{
    for (int i=0; i<n; ++i)
    {
        push_front(new T()); 
    }
}

template<class T>
void LinkedList<T>::push_front(T elem)
{
    start = new LinkedListNode<T>(new T(elem), start);
}

template<class T>
void LinkedList<T>::push_front(T* elem)
{
    start = new LinkedListNode<T>(elem, start);
}

template<class T>
void LinkedList<T>::pop_front()
{
    LinkedListNode<T>* erasingElem = start;
    start = start->next;
    delete erasingElem->item; 
    delete erasingElem; 
}

template<class T>
LinkedList<T>::~LinkedList()
{
    while (start->next != NULL)
    {
        this->pop_front();
    }
}

