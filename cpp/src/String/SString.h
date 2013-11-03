
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
    SString( unsigned int n, const char* );
    SString( unsigned int n, const SString& );
    /** @} */
    
    virtual ~SString ();
    
    unsigned int lenght()const;
    unsigned int maxsize()const;
    
    void resize( unsigned int );
    void clear();
    
    bool empty()const;
    
    /**
    * @defgroup SString element access
    * @{
    */
    const char at( unsigned int )const;
    char       at( unsigned int );
    
    const char* cstr()const;
    /** @} */
    
    SString substr( unsigned int start, unsigned int len )const;
    
    void append( const SString& );
    void append( const char* );
    void append( unsigned int n, char ch );
    void append( unsigned int n, const char* );
    void append( unsigned int n, const SString& );
    
    void push_back ( char ch );
    void push_front( char ch );
    
    char pop_back();
    char pop_front();
    
    void insert( unsigned int start_pos, const SString& s );
    void insert( unsigned int start_pos, const char* cs );
    void insert( unsigned int start_pos, char ch );
    
    void assign( const SString& );
    void assign( const char* );
    void assign( char );
    
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

private:
    unsigned int m_lenght;
    char*        m_cstring;
};


