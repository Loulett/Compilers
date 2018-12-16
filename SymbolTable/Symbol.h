#pragma once

#include <string>
#include <unordered_map>


class Symbol
{
private:
    const std::string& string;

public:
    explicit Symbol( const std::string& string_ );

    const std::string& String() const;

    Symbol() = delete;
    Symbol( const Symbol& ) = delete;
    void operator=( const Symbol& ) = delete;
};
