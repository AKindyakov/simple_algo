
template<class Item> 
class LinkedListNode 
{
public:
    LinkedListNode();
    ~LinkedListNode();
    
    listNode* getNext();
    
private:
    listNode* p_next;
    Item* p_item;
};

template<class Item> 
class DublyLinkedListNode 
{
public:
    DublyLinkedListNode();
    ~DublyLinkedListNode();
    
    listNode* getNext();
    
private:
    listNode* p_next;
    Item* p_item;
};


