#include "../SymbolTable/Symbol.h"
#include "IAccess.h"

class IFrame {
public:
    virtual ~IFrame() = default;
    virtual void AddFormal(const Symbol* name) = 0;
    virtual void AddLocal(const Symbol* name) = 0;
    virtual int FormalsCount() const = 0;
    virtual const IAccess* Formal(int index) const = 0;
    virtual const IAccess* FindLocalOrFormal(const Symbol* name) const = 0;
};
