#pragma once

#include <iostream>
#include <string>

#include "SqlGrammarBaseVisitor.h"

namespace metable {

using namespace std;

class Expr {};

// literal expression base class.
class Literal : Expr {};

// unary expression base class.
class UnaryExpr : protected Expr {
protected:
    Expr expr;

public:
    UnaryExpr(Expr Expr);
};

// binary expression base class.
class BinaryExpr : protected Expr {
protected:
    Expr left;
    Expr right;

public:
    BinaryExpr(Expr left, Expr right);
};

// define structs for all Literal.
class NullLiteral : Literal {};

class StringLiteral : Literal {
    string value;

public:
    StringLiteral(string value);
};

class BooleanLiteral : Literal {
    bool value;

public:
    BooleanLiteral(bool value);
};

class IntegerLiteral : Literal {
    long value;

public:
    IntegerLiteral(long value);
};

class DecimalLiteral : Literal {
    double value;

public:
    DecimalLiteral(double value);
};

// define basic expressions
class ValueExpr : protected UnaryExpr {
public:
    ValueExpr(Expr expr) : UnaryExpr(expr){};
};

class AsteriskExpr : Expr {};

// define unary exprs

class NotExpr : protected UnaryExpr {
public:
    NotExpr(Expr expr) : UnaryExpr(expr){};
};

class ParenExpr : protected UnaryExpr {
public:
    ParenExpr(Expr expr) : UnaryExpr(expr){};
};

class AndExpr : protected BinaryExpr {
public:
    AndExpr(Expr left, Expr right) : BinaryExpr(left, right){};
};

class OrExpr : protected BinaryExpr {
public:
    OrExpr(Expr left, Expr right) : BinaryExpr(left, right){};
}

// TODO logicalPredicate expressions
// TODO arithmeticUnary expressions

// define arithmetic operators
class PlusExpr : protected BinaryExpr {
public:
    PlusExpr(Expr left, Expr right) : BinaryExpr(left, right){};
};

class MinusExpr : protected BinaryExpr {
public:
    MinusExpr(Expr left, Expr right) : BinaryExpr(left, right){};
};

class MultiplyExpr : protected BinaryExpr {
public:
    MultiplyExpr(Expr left, Expr right) : BinaryExpr(left, right){};
};

class DivideExpr : protected BinaryExpr {
public:
    DivideExpr(Expr left, Expr right) : BinaryExpr(left, right){};
};

class ModExpr : protected BinaryExpr {
public:
    ModExpr(Expr left, Expr right) : BinaryExpr(left, right){};
};

// define comparison operators
class LtExpr : protected BinaryExpr {
public:
    LtExpr(Expr left, Expr right) : BinaryExpr(left, right){};
};

class LteExpr : protected BinaryExpr {
public:
    LteExpr(Expr left, Expr right) : BinaryExpr(left, right){};
};

class EqExpr : protected BinaryExpr {
public:
    EqExpr(Expr left, Expr right) : BinaryExpr(left, right){};
};

class GtExpr : protected BinaryExpr {
public:
    GtExpr(Expr left, Expr right) : BinaryExpr(left, right){};
};

class GteExpr : protected BinaryExpr {
public:
    GteExpr(Expr left, Expr right) : BinaryExpr(left, right){};
};

class NeqExpr : protected BinaryExpr {
public:
    NeqExpr(Expr left, Expr right) : BinaryExpr(left, right){};
};

class AliasExpr : Expr {
    Expr expr;
    string alias;

public:
    AliasExpr(Expr expr, string alias);
};

class SqlFrom {
    string tableName;
    string alias;

public:
    SqlFrom(string tableName, string alias);
};

class SqlStatement {};
class SqlSelect : SqlStatement {
    vector<Expr> selectVec;
    SqlFrom from;
    Expr where;

public:
    SqlSelect(vector<Expr> selectVec, SqlFrom from, Expr where);
};

class SqlParser {
public:
    SqlStatement parse(string sql);
};

class MetableSqlVisitor : public SqlGrammarBaseVisitor {
private:
    shared_ptr<SqlSelect> withSqlSelect(
        SqlGrammarParser::SelectClauseContext *selectContext,
        SqlGrammarParser::FromClauseContext *fromContext,
        SqlGrammarParser::WhereClauseContext *whereContext);

public:
    virtual antlrcpp::Any visitQueryStatement(
        SqlGrammarParser::QueryStatementContext *ctx) override {
        return withSqlSelect(ctx->selectClause(), ctx->fromClause(), ctx->whereClause());
    }

    virtual antlrcpp::Any visitSelectClause(
        SqlGrammarParser::SelectClauseContext *ctx) override {
        vector<SqlGrammarParser::NamedExpressionContext *> namedExpressCtxVec =
            ctx->nameExpressionSeq()->namedExpression();
        vector<Expr> exprVec = {};
        for (auto namedExpress : namedExpressCtxVec) {
            exprVec.push_back(visitNamedExpression(namedExpress).as<Expr>());
        }
        return exprVec;
    }

    virtual antlrcpp::Any visitNamedExpression(
        SqlGrammarParser::NamedExpressionContext *ctx) override {
        // TODO 指定别名
        return AliasExpr(visit(ctx->expression()), "");
    }

    // visit all boolean expression.
    virtual antlrcpp::Any visitLogicalNot(
        SqlGrammarParser::LogicalNotContext *ctx) override {
        return NotExpr(visit(ctx->booleanExpression()))
    }

    virtual antlrcpp::Any visitLogicalPredicate(
        SqlGrammarParser::LogicalPredicateContext *ctx) override {
        if (ctx->predicate() == nullptr) {
            return visit(ctx->valueExpression());
        }
        // todo
        return antlrcpp::Any();
    }

    virtual antlrcpp::Any visitLogicalBinary(
        SqlGrammarParser::LogicalBinaryContext *ctx) override {
        Expr leftExpr = visit(ctx->booleanExpression(0).as<Expr>();
        Expr rightExpr = visit(ctx->booleanExpression(1).as<Expr>();
        if (ctx->AND() == nullptr) {
            return OrExpr(left, right);
        } else {
            return AndExpr(left, right);
        }
    }

    // todo visit arithmeticUnary
    

    virtual antlrcpp::Any visitStar(SqlGrammarParser::StarContext *ctx) override {
        return SqlExpression(ASTERISK);
    }
    virtual antlrcpp::Any visitFromClause(
        SqlGrammarParser::FromClauseContext *ctx) override {
        return SqlFrom("test");
    }
};

}  // namespace metable
