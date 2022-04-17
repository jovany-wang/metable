#pragma once

#include <string>

#include "SqlGrammarVisitor.h"

class Stmt {};

class QueryStmt {};

class SqlParser {
public:
    Stmt parse(std::string statement);
};

class MetableSqlVisitor : public SqlGrammarVisitor {
    
};
