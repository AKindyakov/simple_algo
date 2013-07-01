#include <iostream>
#include "LibAlgoCommon.h"

int main ( int _argNum, char** _args )
{
    LinkedList<double> doubleList;
    
    doubleList.push_front(55.1);
    
    double* pDoubleSample = new double;
    *pDoubleSample = 56.2;
    doubleList.push_front(pDoubleSample);
    
    doubleList.push_front(57.3);
    
    LinkedList<double>::Node node = doubleList.getBeginNode(); 
     
    std::cout << "List element " << " -> " << *(doubleList.getBeginNode().item) << "\n";
    std::cout << "List element " << " -> " << *(doubleList.getBeginNode().next->item) << "\n";
    std::cout << "List element " << " -> " << *(doubleList.getBeginNode().next->next->item) << "\n";
    doubleList.pop_front();

    std::cout << "List element " << " -> " << *(doubleList.getBeginNode().item) << "\n";
    std::cout << "List element " << " -> " << *(doubleList.getBeginNode().next->item) << "\n";
    //std::cout << "List element " << " -> " << *(doubleList.getBeginNode().next->next->item) << "\n";
    //doubleList.pop_front();
    
    double it = 0;
    while(1)
    {
        it += 1;
        doubleList.push_front(it);
        std::cout << "List element " << " -> " << *(doubleList.getBeginNode().item) << "\n";
        doubleList.pop_front();
    }
    return 0;
}

