#include "../SymbolTable/Symbol.h"
#include "IAccess.h"

namespace IRTree {

    using namespace IRTree;

    class IFrame {
    public:
        virtual ~IFrame() = default;

        virtual void AddFormal(const std::string& name ) = 0;

        virtual void AddLocal(const std::string& name) = 0;

        //virtual int FormalsCount() const = 0;  //?

//        virtual const IAccess *Formal(int index) const = 0;
//
//        virtual const IAccess *FindLocalOrFormal(const Symbol *name) const = 0;
        virtual void AddAccess( const std::string& name, const IAccess* address ) = 0;

        virtual const IAccess* GetAccess( const std::string& name ) = 0;

        virtual const IExpr* ExternalCall( const std::string& functionName, const ExpressionsList* args ) const = 0;

        virtual const std::string& GetName() = 0;

        virtual int WordSize() const = 0;
    };
}