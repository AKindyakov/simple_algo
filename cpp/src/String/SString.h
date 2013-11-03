
class SString {
    SString();
    SString( const SString& );
    SString( const char* );
    SString( unsigned int n, char ch );
    SString( unsigned int n, const char* );
    SString( unsigned int n, const SString& );
    
    virtual ~SString ();
    
    SString& operator= ( const SString& );
    SString& operator= ( const char* );
    SString& operator= ( char );
    
    unsigned int lenght()const;
    unsigned int maxsize()const;
    
    void resize( unsigned int );
    void clear();
    bool empty()const;
    
    char at( unsigned int )const;
    SString substr(start, len)const;
    
    void append( const SString& );
    void append( const char* );
    void append( unsigned int n, char ch );
    void append( unsigned int n, const char* );
    void append( unsigned int n, const SString& );
    
    void push_back( char ch );
    void push_front(  char ch );
    
    char pop_back();
    char pop_front();
    
    void assign( const SString& );
    void assign( const char* );
    void assign( char );
    
    friend SString operator+( const SString&, const SString& );
};
