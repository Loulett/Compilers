#include "Symbol.h"


Symbol::Symbol( const std::string& string_ ) : string( string_ )
{}

const std::string& Symbol::String() const
{
    return string;
}
