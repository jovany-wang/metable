#include "src/sql/sql_parser.h"

#include <iostream>
#include <vector>

#include "SqlGrammarParser.h"
#include "SqlLexer.h"
#include "antlr4-runtime.h"
#include "common/logging.h"
#include "string"

namespace metable {
using namespace antlr4;
using namespace std;

UnaryExpr::UnaryExpr(Expr expr) : expr(expr){};

BinaryExpr::BinaryExpr(Expr left, Expr right) : left(left), right(right){};

StringLiteral::StringLiteral(string value) : value(value){};

BooleanLiteral::BooleanLiteral(bool value) : value(value){};

IntegerLiteral::IntegerLiteral(long value) : value(value){};

DecimalLiteral::DecimalLiteral(double value) : value(value){};

AliasExpr::AliasExpr(Expr expr, string alias) : expr(expr), alias(alias){};

SqlFrom::SqlFrom(string tableName, string alias) : tableName(tableName), alias(alias){};

SqlSelect::SqlSelect(vector<Expr> selectVec, SqlFrom from, Expr where)
    : selectVec(selectVec), from(from), where(where){};

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

std::shared_ptr<SqlSelect> MetableSqlVisitor::withSqlSelect(
    SqlGrammarParser::SelectClauseContext *selectContext,
    SqlGrammarParser::FromClauseContext *fromClause,
    SqlGrammarParser::WhereClauseContext *whereClause) {
    vector<Expr> express_list = visitSelectClause(selectContext).as<vector<Expr>>();
    SqlFrom from = visitFromClause(fromClause).as<SqlFrom>();
    SqlSelect select = {express_list, from, Expr{}};
    return make_shared<SqlSelect>(select);
}

}  // namespace metable