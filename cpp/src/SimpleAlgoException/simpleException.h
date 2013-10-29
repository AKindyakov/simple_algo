#include <string>
#include <sstream>

class SimpleException {
public:
    SimpleException(const std::string& whatsWrong) 
        : name( whatsWrong ),
          row(-1)  {}
    
    SimpleException(const std::string& whatsWrong, unsigned long int _row) 
        : name( whatsWrong ),
          row(_row) {}
    
    std::string what()const {
        std::stringstream errS;
        errS << name;
        if ( row > 0 ) {
            errS << ". at line : " << row;
        }
        return errS.str();
    }
private:
    long int row;
    std::string name;
};
