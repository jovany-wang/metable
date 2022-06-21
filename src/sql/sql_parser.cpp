#include "src/sql/sql_parser.h"

#include <iostream>
#include <vector>

#include "SqlGrammarParser.h"
#include "SqlLexer.h"
#include "antlr4-runtime.h"
#include "common/logging.h"
#include "string"

using namespace antlr4;
using namespace std;

SqlSelect SqlParser::parse(std::string statement) {
    ANTLRInputStream input(statement);
    SqlLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    SqlGrammarParser parser(&tokens);
    tree::ParseTree *tree = parser.statement();
    MetableSqlVisitor visitor;
    auto x = visitor.visit(tree);
    auto y = x.as<std::shared_ptr<SqlSelect>>();
    return *y;
}

SqlSelect::SqlSelect(std::vector<SqlExpression> selectList, SqlFrom from)
    : from_(std::move(from)) {
    this->selectList = selectList;
}

SqlFrom::SqlFrom(std::string tableIdentify) { this->tableIdentify = tableIdentify; }

std::shared_ptr<SqlSelect> MetableSqlVisitor::withSqlSelect(
    SqlGrammarParser::SelectClauseContext *selectContext,
    SqlGrammarParser::FromClauseContext *fromClause,
    SqlGrammarParser::WhereClauseContext *whereClause) {
    vector<SqlExpression> express_list =
        visitSelectClause(selectContext).as<std::vector<SqlExpression>>();
    SqlFrom from = visitFromClause(fromClause).as<SqlFrom>();
    SqlSelect select = {express_list, from};
    return make_shared<SqlSelect>(select);
}

SqlExpression::SqlExpression(ConstantValue constant) { this->constant = constant; }
