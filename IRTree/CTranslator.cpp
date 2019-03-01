#include "CTranslator.h"
#include "CIRExpression.h"

using namespace IRTree;

void Translator::visit( const IdentifierExpression* n )
{
    MemoryExpression(BINOP(BINOP::PLUS, curFrame->FP(), ConstExpression()))
}
