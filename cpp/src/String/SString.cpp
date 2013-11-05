#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <climits>

#include "SString.h"

SString::SString()
        : m_lenght(0) {
    m_cstring = static_cast< char* >(malloc(1));
    if( m_cstring == NULL ) {
        throw std::bad_alloc();
    }
    *m_cstring = 0;
}

SString::SString( const SString& sstr )
    : m_lenght(sstr.lenght()) {
    m_cstring = sstr.cstr();
}

SString::SString( const char* cstr ) 
    : m_lenght(strlen(cstr)) {
    m_cstring = static_cast<char*>( malloc(m_lenght+1) );
    strcpy(m_cstring, cstr);
}

SString::SString( unsigned int n, char ch )
        : m_lenght(n) {
    m_cstring = static_cast<char*>( malloc(m_lenght+1) );
    memset(m_cstring, ch, n);
    m_cstring[m_lenght] = 0;
}

SString::SString( const SString& tstr, unsigned int start, unsigned int len ) {
    if( start >= tstr.m_lenght ) {
        throw std::out_of_range("SString::substr error, start must low then lenght");
    }
    const char* spt = tstr.m_cstring+start;
    if( start + len > tstr.m_lenght ) {
        len = tstr.m_lenght-start;
    }
    m_lenght = len;
    m_cstring = static_cast<char*>( malloc(m_lenght+1) );
    strncpy(m_cstring, spt, len);
}

SString::~SString () {
    free( static_cast<void*>(m_cstring) );
}

unsigned int SString::lenght()const {
    return m_lenght;
}

unsigned int SString::maxsize()const {
    return UINT_MAX-1;
}

void SString::unsafe_resize( unsigned int new_size ) {
    check_new_len( new_size );
    void* np = realloc( static_cast<void*>(m_cstring), new_size+1 );
    if( np == NULL ) {
        throw std::bad_alloc();
    }
    m_cstring = static_cast<char*>(np);
    m_lenght = new_size;
}

void SString::check_new_len( unsigned int new_size ) {
    if( new_size == UINT_MAX ) {
        throw std::out_of_range("SString::resize error, too great new size");
    }
}

void SString::resize( unsigned int n ) {
    unsigned int of = m_lenght;
    this->unsafe_resize( n );
    if( n > of ) {
        memset( m_cstring+of, 0, n-of );
    }
    m_cstring[m_lenght] = 0;
}

void SString::resize( unsigned int n, char ch ) {
    unsigned int of = m_lenght;
    this->unsafe_resize( n );
    if( n > of ) {
        memset( m_cstring+of, ch, n-of );
    }
    m_cstring[m_lenght] = 0;
}

void SString::clear() {
    this->resize(0);
}

bool SString::empty()const {
    return m_lenght==0;
}

const char& SString::at( unsigned int p )const {
    return this->at(p);
}

char& SString::at( unsigned int p ) {
    if( p >= m_lenght ) {
        throw std::out_of_range("SString::substr error, start must low then lenght");
    }
    return m_cstring[p];
}

char* SString::cstr()const {
    char* str = static_cast<char*>( malloc(m_lenght+1) );
    strcpy(str, m_cstring);
    return str;
}

SString SString::substr( unsigned int start, unsigned int len )const {
    return SString( *this, start, len );
}

void SString::append( const SString& ss ) {
    char* of = &m_cstring[m_lenght];
    unsigned int n = ss.m_lenght + m_lenght;
    this->unsafe_resize( n );
    strcpy( of, ss.m_cstring );
}

void SString::append( const char* cs ) {
    char* of = &m_cstring[m_lenght];
    unsigned int n = strlen(cs) + m_lenght;
    this->unsafe_resize( n );
    strcpy( of, cs );
}

void SString::append( unsigned int n, char ch ) {
    this->resize( m_lenght+n, ch );
}

void SString::push_back ( char ch ) {
    this->resize( m_lenght+1, ch );
}

char SString::pop_back() {
    char ret = this->at(m_lenght-1);
    this->resize( m_lenght-1 );
    return ret;
}

void SString::assign( const SString& ss ) {
    free( static_cast<void*>(m_cstring) );
    m_cstring = ss.cstr();
    m_lenght = ss.lenght();
}

void SString::assign( const char* cs ) {
    this->resize( strlen(cs) );
    strcpy( m_cstring, cs );
}

void SString::assign( char ch ) {
    this->resize( 1 );
    m_cstring[0] = ch;
}

int SString::compare( const SString& ss )const {
    strcmp(m_cstring, ss.m_cstring);
}

int SString::compare( const char* cs)const {
    strcmp(m_cstring, cs);
}

SString& SString::operator= ( const SString& ss ) {
    this->assign( ss );
}

SString& SString::operator= ( const char* cs ) {
    this->assign( cs );
}

SString& SString::operator= ( char ch ) {
    this->assign( ch );
}

SString operator+( const SString& ss1, const SString& ss2 ) {
    SString rezSS(ss1);
    rezSS.append(ss2);
    return rezSS;
}

SString operator+( const char* cs1, const SString& ss2 ) {
    SString rezSS(cs1);
    rezSS.append(ss2);
    return rezSS;
}

SString operator+( const SString& ss1, const char* cs2 ) {
    SString rezSS(ss1);
    rezSS.append(cs2);
    return rezSS;
}

SString& SString::operator+=( const SString& ss ) {
    this->append(ss);
    return *this;
}

SString& SString::operator+=( const char* cs ) {
    this->append(cs);
    return *this;
}

SString& SString::operator+=( char ch ) {
    this->push_back(ch);
    return *this;
}

bool operator==( const SString& ss1, const SString& ss2 ) {
    return 0 == strcmp( ss1.m_cstring, ss2.m_cstring );
}

bool operator==( const char* cs, const SString& ss ) {
    return 0 == strcmp( cs, ss.m_cstring );
}

bool operator==( const SString& ss, const char* cs ) {
    return 0 == strcmp( cs, ss.m_cstring );
}

bool operator!=( const SString& ss1, const SString& ss2 ) {
    return 0 != strcmp( ss1.m_cstring, ss2.m_cstring );
}

bool operator!=( const char* cs, const SString& ss ) {
    return 0 != strcmp( cs, ss.m_cstring );
}

bool operator!=( const SString& ss, const char* cs ) {
    return 0 != strcmp( cs, ss.m_cstring );
}

bool operator<( const SString& ss1, const SString& ss2 ) {
    return 0 < strcmp( ss1.m_cstring, ss2.m_cstring );
}

bool operator<( const char* cs, const SString& ss ) {
    return 0 < strcmp( cs, ss.m_cstring );
}

bool operator<( const SString& ss, const char* cs ) {
    return 0 > strcmp( cs, ss.m_cstring );
}

bool operator<=( const SString& ss1, const SString& ss2) {
    return 0 <= strcmp( ss1.m_cstring, ss2.m_cstring );
}

bool operator<=( const char* cs, const SString& ss ) {
    return 0 <= strcmp( cs, ss.m_cstring );
}

bool operator<=( const SString& ss, const char* cs ){
    return 0 >= strcmp( cs, ss.m_cstring );
}

bool operator>( const SString& ss1, const SString& ss2 ) {
    return 0 > strcmp( ss1.m_cstring, ss2.m_cstring );
}

bool operator>( const char* cs, const SString& ss ) {
    return 0 > strcmp( cs, ss.m_cstring );
}

bool operator>( const SString& ss, const char* cs ) {
    return 0 < strcmp( cs, ss.m_cstring );
}

bool operator>=( const SString& ss1, const SString& ss2 ) {
    return 0 >= strcmp( ss1.m_cstring, ss2.m_cstring );
}

bool operator>=( const char* cs, const SString& ss ) {
    return 0 >= strcmp( cs, ss.m_cstring );
}

bool operator>=( const SString& ss, const char* cs ) {
    return 0 <= strcmp( cs, ss.m_cstring );
}

std::ostream& operator<<( std::ostream& os, const SString& ss) {
    os << ss.m_cstring;
    return os;
}

std::istream& operator>>( std::istream& is, SString& ss) {
    ss.clear();
    char ch = is.get();
    while( ch != ' ' && ch != '\n' && ch != EOF ) {
        ss.push_back(ch);
        ch = is.get();
    }
}

