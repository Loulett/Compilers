#include "Table.h"


bool Table::HasVarDeclared( Symbol* s )
{
    for (auto it = blocks.rbegin(); it != blocks.rend(); ++it) {
        if( (*it)->HasVarDeclared(s)) {
            return true;
        }
    }
    return false;
}
