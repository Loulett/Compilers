#include "InRegAccess.h"

InRegAccess::InRegAccess(std::string name): name(name) {}

IRExpression* InRegAccess::ToExp() {
    return new TempExpression(name);
}
