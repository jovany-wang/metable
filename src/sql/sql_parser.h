#pragma once

#include <iostream>
#include <string>

#include "SqlGrammarBaseVisitor.h"

namespace metable {

class Expr {};
class Literal : Expr {};

// define structs for all Literal.
class NullLiteral : Literal {};

class StringLiteral : Literal {
    std::string value;
};

class BooleanLiteral : Literal {
    bool value;
};

class IntegerLiteral : Literal {
    long value;
};

class DecimalLiteral : Literal {
    double value;
};

// define basic expressions
class ValueExpr : Expr {
    Literal value;
};

class AsteriskExpr : Expr {};

class NotExpr : Expr {
    Expr expr;
};

class AndExpr : Expr {
    Expr left;
    Expr right;
};

// TODO logicalPredicate expressions
// TODO arithmeticUnary expressions

class ParenExpr : Expr {
    Expr expr;
};

// define arithmetic operators
// TODO may be extends TwoParamExpr ?
class PlusExpr : Expr {
    Expr left;
    Expr right;
};

class MinusExpr : Expr {
    Expr left;
    Expr right;
};

class MultiplyExpr : Expr {
    Expr left;
    Expr right;
};

class DivideExpr : Expr {
    Expr left;
    Expr right;
};

class ModExpr : Expr {
    Expr left;
    Expr right;
};

// define comparison operators
class LtExpr : Expr {
    Expr left;
    Expr right;
};

class LteExpr : Expr {
    Expr left;
    Expr right;
};

class EqExpr : Expr {
    Expr left;
    Expr right;
};

class GtExpr : Expr {
    Expr left;
    Expr right;
};

class GteExpr : Expr {
    Expr left;
    Expr right;
};

class NeqExpr : Expr {
    Expr left;
    Expr right;
};

class AliasExpr : Expr {
    Expr expr;
    std::string alias;
};

class SqlFrom {};

class SqlWhere {};

class SqlSelect {
    std::vector<Expr> selectVec;
    SqlFrom from;
    Expr where;
}

class SqlNode {
};

// only support * expression
class SqlExpression : public SqlNode {
private:
    ConstantValue constant;

public:
    SqlExpression(ConstantValue constant);
};

class SqlNamedExpression : public SqlExpression {
private:
    std::string alias;
};
class SqlFrom : public SqlNode {
private:
    std::string tableIdentify;

public:
    SqlFrom(std::string tableIdentify);
};

// select * from table;
class SqlSelect : public SqlNode {
private:
    std::vector<SqlExpression> selectList;
    SqlFrom from_;

public:
    SqlSelect(std::vector<SqlExpression> selectList, SqlFrom from);
};

class SqlParser {
public:
    SqlSelect parse(std::string sql);
};

class MetableSqlVisitor : public SqlGrammarBaseVisitor {
private:
    std::shared_ptr<SqlSelect> withSqlSelect(
        SqlGrammarParser::SelectClauseContext *selectContext,
        SqlGrammarParser::FromClauseContext *fromContext,
        SqlGrammarParser::WhereClauseContext *whereContext);

public:
    virtual antlrcpp::Any visitQueryStatement(
        SqlGrammarParser::QueryStatementContext *ctx) override {
        std::cout << "============== 21" << std::endl;
        return withSqlSelect(ctx->selectClause(), ctx->fromClause(), ctx->whereClause());
    }

    virtual antlrcpp::Any visitSelectClause(
        SqlGrammarParser::SelectClauseContext *ctx) override {
        std::vector<SqlGrammarParser::NamedExpressionContext *> namedExpressCtxVec =
            ctx->nameExpressionSeq()->namedExpression();
        std::vector<SqlExpression> expressVector = {};
        for (auto namedExpress : namedExpressCtxVec) {
            expressVector.push_back(
                visitNamedExpression(namedExpress).as<SqlExpression>());
        }
        std::cout << "=====================10" << std::endl;
        return expressVector;
    }

    virtual antlrcpp::Any visitNamedExpression(
        SqlGrammarParser::NamedExpressionContext *ctx) override {
        // todo skip alias now.
        return visit(ctx->expression());
    }

    virtual antlrcpp::Any visitLogicalPredicate(
        SqlGrammarParser::LogicalPredicateContext *ctx) override {
        if (ctx->predicate() == nullptr) {
            return visit(ctx->valueExpression());
        }
        // todo
        return antlrcpp::Any();
    }

    virtual antlrcpp::Any visitStar(SqlGrammarParser::StarContext *ctx) override {
        return SqlExpression(ASTERISK);
    }
    virtual antlrcpp::Any visitFromClause(
        SqlGrammarParser::FromClauseContext *ctx) override {
        return SqlFrom("test");
    }
};

}  // namespace metable
