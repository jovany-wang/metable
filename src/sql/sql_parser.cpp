#include "src/sql/sql_parser.h"
#include "antlr4-runtime.h"
#include "SqlGrammarParser.h"
#include "SqlLexer.h"

using namespace antlr4;

Stmt SqlParser::parse(std::string statement) 
{
    ANTLRInputStream input(statement);
    SqlLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    SqlGrammarParser parser(&tokens);
    tree::ParseTree *tree = parser.statement();
    
}