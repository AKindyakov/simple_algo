
template<class Item> 
class LinkedListNode 
{
public:
    LinkedListNode(){};
    ~LinkedListNode(){};
    
    LinkedListNode* getNext(){ 
        return new LinkedListNode(); 
    };

    
private:
    LinkedListNode* p_next;
    Item* p_item;
};

template<class Item> 
class DublyLinkedListNode 
{
public:
    DublyLinkedListNode(){};
    ~DublyLinkedListNode(){};
    
    DublyLinkedListNode* getNext() {
        return new DublyLinkedListNode();
    };

    
private:
    DublyLinkedListNode* p_next;
    Item* p_item;
};

template<class T>
class LinkedList
{
public:
    LinkedList(){};
    ~LinkedList(){};
    
    T* begin(); 
    T* end();
    
private:
    LinkedListNode<T>* m_start;
    static LinkedListNode<T>* m_end;
};

template<class T>
class DublyLinkedList
{
public:
    DublyLinkedList(){};
    ~DublyLinkedList(){};
    
private:
    LinkedListNode<T>* start;
    LinkedListNode<T>* end;
};

