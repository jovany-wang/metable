#include "src/sql/sql_parser.h"

#include "SqlGrammarParser.h"
#include "SqlLexer.h"
#include "antlr4-runtime.h"
#include "string"
#include "common/logging.h"
#include <iostream>
#include <vector>

using namespace antlr4;

SqlSelect SqlParser::parse(std::string statement) {
    ANTLRInputStream input(statement);
    SqlLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    SqlGrammarParser parser(&tokens);
    tree::ParseTree *tree = parser.statement();
    MetableSqlVisitor visitor;
    std::cout << "================== 31" << std::endl;
    auto x = visitor.visit(tree);
    std::cout << "================== 41" << std::endl;
    SqlSelect y = x.as<SqlSelect>();
    std::cout << "================== 51" << std::endl;
    return y;
}

SqlSelect::SqlSelect(std::vector<SqlExpression> selectList, SqlFrom from) : from_(std::move(from)) {
    this->selectList = selectList;
}

SqlFrom::SqlFrom(std::string tableIdentify) { this->tableIdentify = tableIdentify; }

SqlSelect MetableSqlVisitor::withSqlSelect(
    SqlGrammarParser::SelectClauseContext *selectContext,
    SqlGrammarParser::FromClauseContext *fromClause,
    SqlGrammarParser::WhereClauseContext *whereClause) {
    std::cout << "================== 11" << std::endl;
    std::vector<SqlExpression> express_list = visitSelectClause(selectContext).as<std::vector<SqlExpression>>();
    std::cout << "================== 12" << std::endl;
    SqlFrom from = visitFromClause(fromClause).as<SqlFrom>();
    std::cout << "================== 13" << std::endl;
    SqlSelect select = {express_list, from};

    std::cout << "================== 14" << std::endl;
    return select;
}

SqlExpression::SqlExpression(ConstantValue constant) { this->constant = constant; }
