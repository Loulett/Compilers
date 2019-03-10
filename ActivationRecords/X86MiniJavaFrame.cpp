#include "X86MiniJavaFrame.h"

X86MiniJavaFrame::X86MiniJavaFrame(Symbol* class_name, Symbol* method_name):
    name(class_name->GetString() + '::' + method_name->GetString()),
    frame_size(0),
    frame_pointer("__frame__"),
    this_pointer("__this__"),
    return_pointer("__return__")
    {
        addresses[frame_pointer] = new InRegAccess(frame_pointer);
        frame_size += word_size;
        addresses[this_pointer] = new InRegAccess(this_pointer);
        frame_size += word_size;
        addresses[return_pointer] = new InRegAccess(return_pointer);
        frame_size += word_size;
    }

void X86MiniJavaFrame::AddLocal(std::string name) {
    addresses[name] = new InFrameAccess(GetAccess(frame_pointer), frame_size);
    frame_size += word_size;
}

void X86MiniJavaFrame::AddFormal(std::string name) {
    addresses[name] = new InFrameAccess(GetAccess(this_pointer), frame_size);
    frame_size += word_size;
}

IAccess* X86MiniJavaFrame::GetAccess(std::string name) {
    auto res = addresses.find(name);
    if (res != nullptr) {
        return res.second;
    }
    else {
        return nullptr;
    }
}

IRExpression* X86MiniJavaFrame::ExternalCall(std::string method_name, IRExpression* args) {
    return new CallExpression(new NameExpression(method_name), new IRExpList(args));
}
