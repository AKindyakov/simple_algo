#include <istream>
#include <ostream>

class SString {
public:
    
    /**
    * @defgroup SString constructors
    * @{
    */
    SString();
    SString( const SString& );
    SString( const char* );
    SString( unsigned int n, char ch );
    SString( const SString&, unsigned int start, unsigned int len );
    /** @} */
    
    virtual ~SString ();
    
    /**
    * @brief Returns the length of the string, in terms of number of characters
    */
    unsigned int lenght()const;
    
    /**
    * @brief Returns the maximum length the string can reach
    */
    unsigned int maxsize()const;
    
    /**
    * @brief Resizes the string to a length of n characters
    */
    void resize( unsigned int n );
    
    /**
    * @brief Resizes the string to a length of n characters
    */
    void resize( unsigned int n, char ch );
    
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
    * @defgroup SString element access
    * @{
    */
    const char& at( unsigned int )const;
    char&       at( unsigned int );
    
    /**
    * @brief Returns a pointer to an array that contains a null-terminated sequence of characters
    */
    char* cstr()const;
    /** @} */
    
    /**
    * @brief Returns a newly constructed string object with its value initialized to a copy of a
    * substring of this object
    */
    SString substr( unsigned int start, unsigned int len )const;
    
    /**
    * @defgroup SString Extends the string by appending additional characters at the end
    * @{
    */
    void append( const SString& );
    void append( const char* );
    void append( unsigned int n, char ch );
    void append( unsigned int n, const char* );
    void append( unsigned int n, const SString& );
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
    * @defgroup SString Assigns a new value to the string, replacing its current contents
    * @{
    */
    void assign( const SString& );
    void assign( const char* );
    void assign( char );
    /** @} */
    
    int compare( const SString& )const;
    int compare( const char* )const;
    
    /**
    * @defgroup SString modify operators
    * @{
    */
    SString& operator= ( const SString& );
    SString& operator= ( const char* );
    SString& operator= ( char );
    
    friend SString operator+( const SString&, const SString& );
    friend SString operator+( const char*,    const SString& );
    friend SString operator+( const SString&, const char* );
    
    SString& operator+=( const SString& );
    SString& operator+=( const char* );
    SString& operator+=( char );
    /** @} */
    
    friend std::ostream& operator<<( std::ostream&, const SString& );
    friend std::istream& operator>>( std::istream&, SString& );

    /**
    * @defgroup SString relational operators
    * @{
    */
    friend bool operator==( const SString&, const SString& );
    friend bool operator==( const char*,    const SString& );
    friend bool operator==( const SString&, const char* );
    
    friend bool operator!=( const SString&, const SString& );
    friend bool operator!=( const char*,    const SString& );
    friend bool operator!=( const SString&, const char* );
    
    friend bool operator<( const SString&, const SString& );
    friend bool operator<( const char*,    const SString& );
    friend bool operator<( const SString&, const char* );
    
    friend bool operator<=( const SString&, const SString& );
    friend bool operator<=( const char*,    const SString& );
    friend bool operator<=( const SString&, const char* );
    
    friend bool operator>( const SString&, const SString& );
    friend bool operator>( const char*,    const SString& );
    friend bool operator>( const SString&, const char* );
    
    friend bool operator>=( const SString&, const SString& );
    friend bool operator>=( const char*,    const SString& );
    friend bool operator>=( const SString&, const char* );
    /** @} */
    
    typedef typename unsigned int size_type;
    
    static size_type min_alloc_size;
    
private:
    
    void unsafe_resize( unsigned int new_size );
    void check_new_len( unsigned int new_size );
    unsigned int m_lenght;
    unsigned int m_allocated;
    char*        m_cstring;
};


