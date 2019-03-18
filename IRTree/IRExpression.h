#pragma once

struct IRVisitor;

class IRExpression {
public:
    IRExpression() = default;
    virtual ~IRExpression() = default;

    virtual void Accept( IRVisitor* v ) const = 0;
};
