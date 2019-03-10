#include <Statement.h>
#include <../ActivationRecords/IAccess.h>

class CodeFragment{
 public:
    CodeFragment(IFrame* frame, IStatement* body): frame(frame), body(body) {}

    IFrame* frame;
    IStatement* body;
};
