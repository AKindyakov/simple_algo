#include "ListContainer/LinkedList.h"

template<class T>
T* LinkedList<T>::begin()
{
    return m_start; 
}

template<class T>
T* LinkedList<T>::end()
{
    return m_end; 
}

template<class T>
LinkedListNode<T>* LinkedList<T>::m_end = new LinkedListNode<T>();
