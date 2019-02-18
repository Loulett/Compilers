#pragma once
#include "../AST/ITreeNodes.h"


class IRMoveStatement : public IStatement {

 public:
    IRMoveStatement();

 private:
};

class IRExpressionStatement : public IStatement {

 public:
    IRExpressionStatement();

 private:
};

class IRJumpStatement : public IStatement {

 public:
    IRJumpStatement();

 private:
};

class IRCJumpStatement : public IStatement {

 public:
    IRCJumpStatement();

 private:
};

class IRSeqStatement : public IStatement {

 public:
    IRSeqStatement();

 private:
};

class IRLabelStatement : public IStatement {

 public:
    IRLabelStatement();

 private:
};