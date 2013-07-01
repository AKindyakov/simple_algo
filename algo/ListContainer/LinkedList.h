#include <cstdlib>

template<class Item>
class LinkedList
{
public:
    
    struct Node
    {
        Node();
        Node(Item* const, Node* const );
        Node(const Node& cp);
        
        virtual ~Node();
        Node* next;
        Item* item;
    };
    
    LinkedList();
    LinkedList(int size);
    virtual ~LinkedList();
   
    void push_front(const Item& ); 
    void push_front(Item* const); 
    void pop_front(); 
    
    void erase(const Node* begin, const Node* end); 
    void erase(const Node* ); 
    
    Item getBegin() { return *start->item; }; 
    Node getBeginNode() { return *start; }; 
 
private:
    Node* start;
};

template<class Item>
class DublyLinkedList
{
public:
    class Node
    {
    public:
        Node(){};
        ~Node(){};
            
        Node* next;
        Node* prev;
        Item* item;
    };
    
    DublyLinkedList(){};
    ~DublyLinkedList(){};
    
    Item getFront() { return *start->item }; 
    Item getBack() { return *end->item }; 
    
    Node* getBeginNode();
    Node* getEndNode();    
    
private:
    Node* start;
    Node* end;

};

template<class Item> 
LinkedList<Item>::Node::Node()
    : item(NULL), next(NULL) 
{}

template<class Item> 
LinkedList<Item>::Node::Node( Item* const _pItem, 
                              Node* const _pNode )
    : item(_pItem), next(_pNode) 
{}

template<class Item> 
LinkedList<Item>::Node::Node(const Node& cp)
    : item(cp.item), next(cp.next)
{}

template<class Item> 
LinkedList<Item>::Node::~Node()
{}

template<class T>
LinkedList<T>::LinkedList()
    : start(new Node())
{}

template<class T>
LinkedList<T>::LinkedList(int n)
    : start(new Node())
{
    for (int i=0; i<n; ++i)
    {
        push_front(new T()); 
    }
}

template<class T>
void LinkedList<T>::push_front(const T& elem)
{
    start = new Node(new T(elem), start);
}

template<class T>
void LinkedList<T>::push_front(T* const elem)
{
    start = new Node(elem, start);
}

template<class T>
void LinkedList<T>::pop_front()
{
    Node* erasingElem = start;
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

