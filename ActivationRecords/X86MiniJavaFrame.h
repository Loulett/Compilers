#include "IFrame.h"
#include "../SymbolTree/Symbol.h"
#include <string>
#include <map>

class X86MiniJavaFrame: public IFrame {
 public:
    X86MiniJavaFrame(Symbol* class_name, Symbol* method_name);
    void AddFormal(std::string name) override;
    void AddLocal(std::string name) override;
    IAccess* GetAccess(std::string name);
    IRExpression ExternalCall(std::string name, IRExpression* args);
    // int FormalsCount() override;
    // IAccess* Formal(int index) override;
    // IAccess* FindLocalOrFormal(const Symbol* name) override;
 private:
    std::string name;
    const static std::string frame_pointer;
    const static std::string this_pointer;
    const static std::string return_pointer;
    int frame_size;
    const int word_size = 4;
    std::map<std::string, IAccess*> addresses;
};
