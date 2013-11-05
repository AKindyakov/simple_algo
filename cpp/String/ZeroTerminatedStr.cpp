#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <climits>

#include "ZeroTerminatedStr.h"

ZeroTerminatedStr::ZeroTerminatedStr()
        : m_lenght(0) {
    m_cstring = static_cast< char* >(malloc(1));
    if( m_cstring == NULL ) {
        throw std::bad_alloc();
    }
    *m_cstring = 0;
}

ZeroTerminatedStr::ZeroTerminatedStr( const ZeroTerminatedStr& sstr )
    : m_lenght(sstr.lenght()) {
    m_cstring = sstr.cstr();
}

ZeroTerminatedStr::ZeroTerminatedStr( const char* cstr ) 
    : m_lenght(strlen(cstr)) {
    m_cstring = static_cast<char*>( malloc(m_lenght+1) );
    strcpy(m_cstring, cstr);
}

ZeroTerminatedStr::ZeroTerminatedStr( size_t n, char ch )
        : m_lenght(n) {
    m_cstring = static_cast<char*>( malloc(m_lenght+1) );
    memset(m_cstring, ch, n);
    m_cstring[m_lenght] = 0;
}

ZeroTerminatedStr::ZeroTerminatedStr( const ZeroTerminatedStr& tstr, size_t start, size_t len ) {
    if( start >= tstr.m_lenght ) {
        throw std::out_of_range("ZeroTerminatedStr::substr error, start must low then lenght");
    }
    const char* spt = tstr.m_cstring+start;
    if( start + len > tstr.m_lenght ) {
        len = tstr.m_lenght-start;
    }
    m_lenght = len;
    m_cstring = static_cast<char*>( malloc(m_lenght+1) );
    strncpy(m_cstring, spt, len);
}

ZeroTerminatedStr::~ZeroTerminatedStr () {
    free( static_cast<void*>(m_cstring) );
}

size_t ZeroTerminatedStr::lenght()const {
    return m_lenght;
}

size_t ZeroTerminatedStr::maxsize()const {
    return static_cast<size_t>(INT_MAX-1);
}

void ZeroTerminatedStr::unsafe_resize( size_t new_size ) {
    check_new_len( new_size );
    void* np = realloc( static_cast<void*>(m_cstring), new_size+1 );
    if( np == NULL ) {
        throw std::bad_alloc();
    }
    m_cstring = static_cast<char*>(np);
    m_lenght = new_size;
}

void ZeroTerminatedStr::check_new_len( size_t new_size ) {
    if( new_size == UINT_MAX ) {
        throw std::out_of_range("ZeroTerminatedStr::resize error, too great new size");
    }
}

void ZeroTerminatedStr::resize( size_t n ) {
    size_t of = m_lenght;
    this->unsafe_resize( n );
    if( n > of ) {
        memset( m_cstring+of, 0, n-of );
    }
    m_cstring[m_lenght] = 0;
}

void ZeroTerminatedStr::resize( size_t n, char ch ) {
    size_t of = m_lenght;
    this->unsafe_resize( n );
    if( n > of ) {
        memset( m_cstring+of, ch, n-of );
    }
    m_cstring[m_lenght] = 0;
}

void ZeroTerminatedStr::clear() {
    this->resize(0);
}

bool ZeroTerminatedStr::empty()const {
    return m_lenght==0;
}

const char& ZeroTerminatedStr::at( size_t p )const {
    return this->at(p);
}

char& ZeroTerminatedStr::at( size_t p ) {
    if( p >= m_lenght ) {
        throw std::out_of_range("ZeroTerminatedStr::substr error, start must low then lenght");
    }
    return m_cstring[p];
}

char* ZeroTerminatedStr::cstr()const {
    char* str = static_cast<char*>( malloc(m_lenght+1) );
    strcpy(str, m_cstring);
    return str;
}

ZeroTerminatedStr ZeroTerminatedStr::substr( size_t start, size_t len )const {
    return ZeroTerminatedStr( *this, start, len );
}

void ZeroTerminatedStr::append( const ZeroTerminatedStr& ss ) {
    char* of = &m_cstring[m_lenght];
    size_t n = ss.m_lenght + m_lenght;
    this->unsafe_resize( n );
    strcpy( of, ss.m_cstring );
}

void ZeroTerminatedStr::append( const char* cs ) {
    char* of = &m_cstring[m_lenght];
    size_t n = strlen(cs) + m_lenght;
    this->unsafe_resize( n );
    strcpy( of, cs );
}

void ZeroTerminatedStr::append( size_t n, char ch ) {
    this->resize( m_lenght+n, ch );
}

void ZeroTerminatedStr::push_back ( char ch ) {
    this->resize( m_lenght+1, ch );
}

char ZeroTerminatedStr::pop_back() {
    char ret = this->at(m_lenght-1);
    this->resize( m_lenght-1 );
    return ret;
}

void ZeroTerminatedStr::assign( const ZeroTerminatedStr& ss ) {
    free( static_cast<void*>(m_cstring) );
    m_cstring = ss.cstr();
    m_lenght = ss.lenght();
}

void ZeroTerminatedStr::assign( const char* cs ) {
    this->resize( strlen(cs) );
    strcpy( m_cstring, cs );
}

void ZeroTerminatedStr::assign( char ch ) {
    this->resize( 1 );
    m_cstring[0] = ch;
}

int ZeroTerminatedStr::compare( const ZeroTerminatedStr& ss )const {
    strcmp(m_cstring, ss.m_cstring);
}

int ZeroTerminatedStr::compare( const char* cs)const {
    strcmp(m_cstring, cs);
}

ZeroTerminatedStr& ZeroTerminatedStr::operator= ( const ZeroTerminatedStr& ss ) {
    this->assign( ss );
}

ZeroTerminatedStr& ZeroTerminatedStr::operator= ( const char* cs ) {
    this->assign( cs );
}

ZeroTerminatedStr& ZeroTerminatedStr::operator= ( char ch ) {
    this->assign( ch );
}

ZeroTerminatedStr operator+( const ZeroTerminatedStr& ss1, const ZeroTerminatedStr& ss2 ) {
    ZeroTerminatedStr rezSS(ss1);
    rezSS.append(ss2);
    return rezSS;
}

ZeroTerminatedStr operator+( const char* cs1, const ZeroTerminatedStr& ss2 ) {
    ZeroTerminatedStr rezSS(cs1);
    rezSS.append(ss2);
    return rezSS;
}

ZeroTerminatedStr operator+( const ZeroTerminatedStr& ss1, const char* cs2 ) {
    ZeroTerminatedStr rezSS(ss1);
    rezSS.append(cs2);
    return rezSS;
}

ZeroTerminatedStr& ZeroTerminatedStr::operator+=( const ZeroTerminatedStr& ss ) {
    this->append(ss);
    return *this;
}

ZeroTerminatedStr& ZeroTerminatedStr::operator+=( const char* cs ) {
    this->append(cs);
    return *this;
}

ZeroTerminatedStr& ZeroTerminatedStr::operator+=( char ch ) {
    this->push_back(ch);
    return *this;
}

bool operator==( const ZeroTerminatedStr& ss1, const ZeroTerminatedStr& ss2 ) {
    return 0 == strcmp( ss1.m_cstring, ss2.m_cstring );
}

bool operator==( const char* cs, const ZeroTerminatedStr& ss ) {
    return 0 == strcmp( cs, ss.m_cstring );
}

bool operator==( const ZeroTerminatedStr& ss, const char* cs ) {
    return 0 == strcmp( cs, ss.m_cstring );
}

bool operator!=( const ZeroTerminatedStr& ss1, const ZeroTerminatedStr& ss2 ) {
    return 0 != strcmp( ss1.m_cstring, ss2.m_cstring );
}

bool operator!=( const char* cs, const ZeroTerminatedStr& ss ) {
    return 0 != strcmp( cs, ss.m_cstring );
}

bool operator!=( const ZeroTerminatedStr& ss, const char* cs ) {
    return 0 != strcmp( cs, ss.m_cstring );
}

bool operator<( const ZeroTerminatedStr& ss1, const ZeroTerminatedStr& ss2 ) {
    return 0 < strcmp( ss1.m_cstring, ss2.m_cstring );
}

bool operator<( const char* cs, const ZeroTerminatedStr& ss ) {
    return 0 < strcmp( cs, ss.m_cstring );
}

bool operator<( const ZeroTerminatedStr& ss, const char* cs ) {
    return 0 > strcmp( cs, ss.m_cstring );
}

bool operator<=( const ZeroTerminatedStr& ss1, const ZeroTerminatedStr& ss2) {
    return 0 <= strcmp( ss1.m_cstring, ss2.m_cstring );
}

bool operator<=( const char* cs, const ZeroTerminatedStr& ss ) {
    return 0 <= strcmp( cs, ss.m_cstring );
}

bool operator<=( const ZeroTerminatedStr& ss, const char* cs ){
    return 0 >= strcmp( cs, ss.m_cstring );
}

bool operator>( const ZeroTerminatedStr& ss1, const ZeroTerminatedStr& ss2 ) {
    return 0 > strcmp( ss1.m_cstring, ss2.m_cstring );
}

bool operator>( const char* cs, const ZeroTerminatedStr& ss ) {
    return 0 > strcmp( cs, ss.m_cstring );
}

bool operator>( const ZeroTerminatedStr& ss, const char* cs ) {
    return 0 < strcmp( cs, ss.m_cstring );
}

bool operator>=( const ZeroTerminatedStr& ss1, const ZeroTerminatedStr& ss2 ) {
    return 0 >= strcmp( ss1.m_cstring, ss2.m_cstring );
}

bool operator>=( const char* cs, const ZeroTerminatedStr& ss ) {
    return 0 >= strcmp( cs, ss.m_cstring );
}

bool operator>=( const ZeroTerminatedStr& ss, const char* cs ) {
    return 0 <= strcmp( cs, ss.m_cstring );
}

std::ostream& operator<<( std::ostream& os, const ZeroTerminatedStr& ss) {
    os << ss.m_cstring;
    return os;
}

std::istream& operator>>( std::istream& is, ZeroTerminatedStr& ss) {
    ss.clear();
    char ch = is.get();
    while( ch != ' ' && ch != '\n' && ch != EOF ) {
        ss.push_back(ch);
        ch = is.get();
    }
}

