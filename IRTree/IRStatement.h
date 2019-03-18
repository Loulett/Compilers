#pragma once

struct IRVisitor;

class IRStatement {
public:
    IRStatement() = default;
    virtual ~IRStatement() = default;

    virtual void Accept( IRVisitor* v ) const = 0;
};
