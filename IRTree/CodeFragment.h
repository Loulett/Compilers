#include "IRStatement.h"
#include "../ActivationRecords/IFrame.h"

class CodeFragment{
 public:
    CodeFragment(IFrame* frame, IRStatement* body): frame(frame), body(body) {}

    IFrame* frame;
    IRStatement* body;
};
