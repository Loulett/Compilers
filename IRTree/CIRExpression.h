#pragma once
#include "../AST/ITreeNodes.h"


class CRConstExpression : public IExpression {

 public:
    IRConstExpression();

 private:

};

class IRNameExpression : public IExpression {

 public:
    IRNameExpression();

 private:
};

class IRTempExpression : public IExpression {

 public:
    IRTempExpression();

 private:

};

class IRBinaryExpression : public IExpression {

 public:
    IRBinaryExpression();

 private:

};

class IRMemoryExpression : public IExpression {

 public:
    IRMemoryExpression();

 private:

};

class IRCallExpression : public IExpression {

 public:
    IRCallExpression();

 private:

};

class IRESEQExpression : public IExpression {

 public:
    IRESEQExpression();

 private:

};