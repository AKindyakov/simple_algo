#include <istream>
#include <ostream>

class ZeroTerminatedStr {
public:
    
    /**
    * @defgroup ZeroTerminatedStr constructors
    * @{
    */
    ZeroTerminatedStr();
    ZeroTerminatedStr( const ZeroTerminatedStr& );
    ZeroTerminatedStr( const char* );
    ZeroTerminatedStr( size_t n, char ch );
    ZeroTerminatedStr( const ZeroTerminatedStr&, size_t start, size_t len );
    /** @} */
    
    virtual ~ZeroTerminatedStr ();
    
    /**
    * @brief Returns the length of the string, in terms of number of characters
    */
    size_t lenght()const;
    
    /**
    * @brief Returns the maximum length the string can reach
    */
    size_t maxsize()const;
    
    /**
    * @brief Resizes the string to a length of n characters
    */
    void resize( size_t n );
    
    /**
    * @brief Resizes the string to a length of n characters
    */
    void resize( size_t n, char ch );
    
    /**
    * @brief Erases the contents of the string, which becomes an empty string 
    * (with a length of 0 characters)
    */
    void clear();
    
    /**
    * @brief Returns whether the string is empty (i.e. whether its length is 0)
    */
    bool empty()const;
    
    /**
    * @defgroup ZeroTerminatedStr element access
    * @{
    */
    const char& at( size_t )const;
    char&       at( size_t );
    
    /**
    * @brief Returns a pointer to an array that contains a null-terminated sequence of characters
    */
    char* cstr()const;
    /** @} */
    
    /**
    * @brief Returns a newly constructed string object with its value initialized to a copy of a
    * substring of this object
    */
    ZeroTerminatedStr substr( size_t start, size_t len )const;
    
    /**
    * @defgroup ZeroTerminatedStr Extends the string by appending additional characters at the end
    * @{
    */
    void append( const ZeroTerminatedStr& );
    void append( const char* );
    void append( size_t n, char ch );
    void append( size_t n, const char* );
    void append( size_t n, const ZeroTerminatedStr& );
    /** @} */
    
    /**
    * @brief resize string, add ch char to the end of string
    */
    void push_back ( char ch );
    
    /**
    * @brief resize string, delete last element from the end of string
    */
    char pop_back();
    
    /**
    * @defgroup ZeroTerminatedStr Assigns a new value to the string, replacing its current contents
    * @{
    */
    void assign( const ZeroTerminatedStr& );
    void assign( const char* );
    void assign( char );
    /** @} */
    
    int compare( const ZeroTerminatedStr& )const;
    int compare( const char* )const;
    
    /**
    * @defgroup ZeroTerminatedStr modify operators
    * @{
    */
    ZeroTerminatedStr& operator= ( const ZeroTerminatedStr& );
    ZeroTerminatedStr& operator= ( const char* );
    ZeroTerminatedStr& operator= ( char );
    
    friend ZeroTerminatedStr operator+( const ZeroTerminatedStr&, const ZeroTerminatedStr& );
    friend ZeroTerminatedStr operator+( const char*,    const ZeroTerminatedStr& );
    friend ZeroTerminatedStr operator+( const ZeroTerminatedStr&, const char* );
    
    ZeroTerminatedStr& operator+=( const ZeroTerminatedStr& );
    ZeroTerminatedStr& operator+=( const char* );
    ZeroTerminatedStr& operator+=( char );
    /** @} */
    
    friend std::ostream& operator<<( std::ostream&, const ZeroTerminatedStr& );
    friend std::istream& operator>>( std::istream&, ZeroTerminatedStr& );

    /**
    * @defgroup ZeroTerminatedStr relational operators
    * @{
    */
    friend bool operator==( const ZeroTerminatedStr&, const ZeroTerminatedStr& );
    friend bool operator==( const char*,              const ZeroTerminatedStr& );
    friend bool operator==( const ZeroTerminatedStr&, const char* );
    
    friend bool operator!=( const ZeroTerminatedStr&, const ZeroTerminatedStr& );
    friend bool operator!=( const char*,              const ZeroTerminatedStr& );
    friend bool operator!=( const ZeroTerminatedStr&, const char* );
    
    friend bool operator<( const ZeroTerminatedStr&, const ZeroTerminatedStr& );
    friend bool operator<( const char*,              const ZeroTerminatedStr& );
    friend bool operator<( const ZeroTerminatedStr&, const char* );
    
    friend bool operator<=( const ZeroTerminatedStr&, const ZeroTerminatedStr& );
    friend bool operator<=( const char*,              const ZeroTerminatedStr& );
    friend bool operator<=( const ZeroTerminatedStr&, const char* );
    
    friend bool operator>( const ZeroTerminatedStr&, const ZeroTerminatedStr& );
    friend bool operator>( const char*,              const ZeroTerminatedStr& );
    friend bool operator>( const ZeroTerminatedStr&, const char* );
    
    friend bool operator>=( const ZeroTerminatedStr&, const ZeroTerminatedStr& );
    friend bool operator>=( const char*,              const ZeroTerminatedStr& );
    friend bool operator>=( const ZeroTerminatedStr&, const char* );
    /** @} */

private:
    
    void unsafe_resize( size_t new_size );
    void check_new_len( size_t new_size );
    size_t m_lenght;
    char*  m_cstring;
};


