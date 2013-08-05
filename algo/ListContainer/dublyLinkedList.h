
class StoredObject {
public:
    StoredObject();
    StoredObject(int _value);
    StoredObject(const StoredObject&);
    virtual ~StoredObject(){};

private:
    int value;
    int mass[255];
};

class DublyList {
public:
    
    DublyList();
    virtual ~DublyList();
    
    void push_back( const StoredObject& );
    void push_back( StoredObject* );
    
    void push_front( const StoredObject& );
    void push_front( StoredObject* );
    
    void pop_back();
    void pop_front();
    
    class Node {
    public:
        Node();
        Node(StoredObject* store);
        Node(StoredObject* store, Node* _next, Node* _prev );
        Node(const Node&);
        virtual ~Node();
        
        StoredObject* object;
        Node* next;
        Node* prev;
    };
    
    Node* getBegin();
    const Node* getConstBegin();
        
    Node* getEnd();
    const Node* getConstEnd();
    
private:
    Node* begin;
    Node* end;
};

