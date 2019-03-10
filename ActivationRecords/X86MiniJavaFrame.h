#include "IFrame.h"

namespace IRTree
{

    class X86MiniJavaFrame: public IFrame
    {
        std::string name;
        std::unordered_map<std::string, std::unique_ptr<const IAccess>> addresses;
        int frameSize;

    public:
        const static std::string FP;
        const static std::string THIS;
        const static std::string RET;

        X86MiniJavaFrame( const Symbol* classSymbol, const Symbol* methodSymbol )
                : name( classSymbol->String() + "::" + methodSymbol->String() ),
                  frameSize( 0 )
        {
            AddAccess( FP, new InFrameAccess( TempExpression( FP ) ) );
            AddAccess( THIS, new InRegAccess( TempExpression( THIS ) ) );
            AddAccess( RET, new InRegAccess( TempExpression( RET ) ) );
        }

        const std::string& GetName() override
        {
            return name;
        }

        int WordSize() const override
        {
            return 4;
        }

        void AddFormal( const std::string& name ) override
        {
            AddAccess( name, new InFrameAccess( GetAccess( THIS ), frameSize ) );
            frameSize += WordSize();
        }

        void AddLocal( const std::string& name ) override
        {
            AddAccess( name, new InFrameAccess( GetAccess( FP ), frameSize ) );
            frameSize += WordSize();
        }

        void AddAccess( const std::string& name, const IAccess* address ) override
        {
            addresses[name] = std::unique_ptr<const IAccess>( address );
        }

        const IAccess* GetAccess( const std::string& name ) override
        {
            auto res = addresses.find( name );
            if( res != addresses.end() ) {
                return res->second.get();
            } else {
                return nullptr;
            }
        }

        const IExpr* ExternalCall( const std::string& functionName, const ExpressionsList* args ) const override
        {
            return new CallExpression( new NameExpression( new Label( functionName ) ), args );
        }

    };
}
