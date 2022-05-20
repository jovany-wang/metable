#include "src/sql/sql_parser.h"

#include "SqlGrammarParser.h"
#include "SqlLexer.h"
#include "antlr4-runtime.h"
#include "string"

using namespace antlr4;

SqlSelect SqlParser::parse(std::string statement) {
    ANTLRInputStream input(statement);
    SqlLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    SqlGrammarParser parser(&tokens);
    tree::ParseTree *tree = parser.statement();
    MetableSqlVisitor visitor;
    return visitor.visit(tree).as<SqlSelect>();
}

SqlSelect::SqlSelect(std::vector<SqlExpression> selectList, SqlFrom from) : from_(std::move(from)) {
    this->selectList = selectList;
}

SqlFrom::SqlFrom(std::string tableIdentify) { this->tableIdentify = tableIdentify; }

SqlSelect MetableSqlVisitor::withSqlSelect(
    SqlGrammarParser::SelectClauseContext *selectContext,
    SqlGrammarParser::FromClauseContext *fromClause,
    SqlGrammarParser::WhereClauseContext *whereClause) {
    SqlSelect select = {visitSelectClause(selectContext).as<std::vector<SqlExpression>>(),
                        visitFromClause(fromClause).as<SqlFrom>()};
}

SqlExpression::SqlExpression(ConstantValue constant) { this->constant = constant; }
