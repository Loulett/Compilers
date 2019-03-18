#include "IRStatement.h"
#include "../ActivationRecords/IFrame.h"

class CodeFragment{
 public:

    CodeFragment(IFrame* frame, IRStatement* body): frame(frame), body(body) {}

    CodeFragment(CodeFragment&& other): frame(std::move(other.frame)), body(std::move(other.body)) {}

    IFrame* frame;
    IRStatement* body;
};
