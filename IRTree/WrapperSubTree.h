//
#pragma once
#include <cassert>
#include "IStm.h"
#include "IExpr.h"
#include "CIRExpression.h"
#include "CIRStatement.h"

namespace IRTree {

    class WrapperSubtree {
    public:
        virtual ~WrapperSubtree() = default;

        virtual const IExpr *ToExp() const = 0;

        virtual const IStatement *ToStm() const = 0;

        virtual const IStatement *ToConditional(const Label *t,
                                                        const Label *f) const = 0;
    };

    class WrapperExpr : public WrapperSubtree {
    public:
        explicit WrapperExpr(const IExpr *e) : expr(e) {
        }

        const IExpr *ToExp() const override {
            return expr;
        }

        const IStm *ToStm() const override {
            return new ExpressionStatement(expr);
        }

        const IStm *ToConditional(const Label *t, const Label *f) const override {
            return new CJumpStatement(CJumpStatement::ERelationType::LT,
                                              expr,
                                              static_cast<IExpr *>(new ConstExpression(0)),
                                              t,
                                              f);
        }

    public:
        const IExpr *expr;
    };

    class WrapperStmt : public WrapperSubtree {
    public:
        explicit WrapperStmt(const IStatement *s) : stmt(s) {
        }

        const IExpr *ToExp() const override {
            assert(false);
        }

        const IStatement *ToStm() const override {
            return stmt;
        }

        const IStatement *ToConditional(const Label *t, const Label *f) const override {
            assert(false);
        }

    public:
        const IStatement *stmt;
    };
}