SString::SString()
    : m_lenght(0),
      m_cstring(NULL) {}

SString::SString( const SString& ) {
}

SString::SString( const char* ) {}
SString::SString( unsigned int n, char ch ) {}
SString::SString( unsigned int n, const char* ) {}
SString::SString( unsigned int n, const SString& ) {}

SString::~SString () {}

unsigned int SString::lenght()const {}
unsigned int SString::maxsize()const {}

void SString::resize( unsigned int ) {}
void SString::clear() {}

bool SString::empty()const {}

const char SString::at( unsigned int )const {}
char SString::at( unsigned int ) {}

const char* SString::cstr()const {}

SString SString::substr( unsigned int start, unsigned int len )const {}

void SString::append( const SString& ) {}
void SString::append( const char* ) {}
void SString::append( unsigned int n, char ch ) {}
void SString::append( unsigned int n, const char* ) {}
void SString::append( unsigned int n, const SString& ) {}

void SString::push_back ( char ch ) {}
void SString::push_front( char ch ) {}

char SString::pop_back() {}
char SString::pop_front() {}

void SString::insert( unsigned int start_pos, const SString& s ) {}
void SString::insert( unsigned int start_pos, const char* cs ) {}
void SString::insert( unsigned int start_pos, char ch ) {}

void SString::assign( const SString& ) {}
void SString::assign( const char* ) {}
void SString::assign( char ) {}

int SString::compare( const SString& )const {}
int SString::compare( const char* )const {}

SString& SString::operator= ( const SString& ) {}
SString& SString::operator= ( const char* ) {}
SString& SString::operator= ( char ) {}

SString operator+( const SString&, const SString& ) {}
SString operator+( const char*,    const SString& ) {}
SString operator+( const SString&, const char* ) {}

SString& SString::operator+=( const SString& ) {}
SString& SString::operator+=( const char* ) {}
SString& SString::operator+=( char ) {}
    
operator==( const SString&, const SString& ) {}
operator==( const char*,    const SString& ) {}
operator==( const SString&, const char* ) {}

operator!=( const SString&, const SString& ) {}
operator!=( const char*,    const SString& ) {}
operator!=( const SString&, const char* ) {}

operator<( const SString&, const SString& ) {}
operator<( const char*,    const SString& ) {}
operator<( const SString&, const char* ) {}

operator<=( const SString&, const SString& ) {
}

operator<=( const char*,    const SString& ) {
}

operator<=( const SString&, const char* ) {
}

operator>( const SString&, const SString& ) {
}

operator>( const char*,    const SString& ) {
}

operator>( const SString&, const char* ) {
}

operator>=( const SString&, const SString& ) {
}

operator>=( const char*,    const SString& ) {
}

operator>=( const SString&, const char* ) {
}

