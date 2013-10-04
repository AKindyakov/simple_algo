#include <cstddef>
#include "dublyLinkedList.h"


StoredObject::StoredObject()
    : value(0) { 
}

StoredObject::StoredObject(int _value) 
    : value(_value) { 
}

StoredObject::StoredObject(const StoredObject& obj)
    : value(obj.value) { 
}

DublyList::DublyList() {
    begin = NULL;
    end   = NULL;
}

DublyList::~DublyList() {
    while (getConstBegin()->object != NULL) {
        this->pop_front();
    }
}

void DublyList::push_back( const StoredObject& obj ) {
    StoredObject* pObj = new StoredObject(obj);
    this->push_back(pObj);
}

void DublyList::push_back( StoredObject* pObj ) {
    if (end != NULL) {
        end = new Node( pObj, NULL, end );
    }
    else {
        begin = new Node( pObj );
        end   = new Node( pObj );
    }
}

void DublyList::push_front( const StoredObject& obj ) {
    StoredObject* pNewObj = new StoredObject(obj);
    this->push_front( pNewObj );
}

void DublyList::push_front( StoredObject* pObj ) {
    if (begin != NULL) {
        begin = new Node( pObj, begin, NULL );
    }
    else {
        begin = new Node( pObj );
        end   = new Node( pObj );
    }
}

void DublyList::pop_back() {
    Node* tmp = end;   
    end = end->prev;
    delete tmp;
}

void DublyList::pop_front() {
    Node* tmp = begin;
    begin = begin->prev;
    delete tmp;
}

DublyList::Node* DublyList::getBegin() {
    return begin;
}

const DublyList::Node* DublyList::getConstBegin() {
    return static_cast< const Node* >(begin);
}
        
DublyList::Node* DublyList::getEnd() {
    return end;
}

const DublyList::Node* DublyList::getConstEnd() {
    return static_cast< const Node* >(end);
}

DublyList::Node::Node() 
    : prev(NULL), object(NULL), next(NULL) {
}

DublyList::Node::Node(StoredObject* store)
    : prev(NULL), object(store), next(NULL) {
}

DublyList::Node::Node(StoredObject* store, Node* _next, Node* _prev )
    : prev(_prev), object(store), next(_next) {
}

DublyList::Node::Node(const Node& nd)
    : prev(nd.prev), object(nd.object), next(nd.next) {
}

DublyList::Node::~Node() {
    delete object;
}

