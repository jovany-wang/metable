#pragma once

#include <iostream>
#include <string>

#include "SqlGrammarBaseVisitor.h"

enum ConstantValue {
    ASTERISK,
};

class SqlNode {};

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
    SqlFrom from;

public:
    SqlSelect(std::vector<SqlExpression> selectList, SqlFrom from);
};

class SqlParser {
public:
    SqlSelect parser(std::string sql);
};

class MetableSqlVisitor : public SqlGrammarBaseVisitor {
private:
    SqlSelect withSqlSelect(SqlGrammarParser::SelectClauseContext *selectContext,
                            SqlGrammarParser::FromClauseContext *fromContext,
                            SqlGrammarParser::WhereClauseContext *whereContext);

public:
    virtual antlrcpp::Any visitQueryStatement(
        SqlGrammarParser::QueryStatementContext *ctx) override {
        return withSqlSelect(ctx->selectClause(), ctx->fromClause(), ctx->whereClause());
    }

    virtual antlrcpp::Any visitSelectClause(
        SqlGrammarParser::SelectClauseContext *ctx) override {
        std::vector<SqlGrammarParser::NamedExpressionContext *> namedExpressCtxVec =
            ctx->nameExpressionSeq()->namedExpression();
        std::vector<SqlExpression> expressVector = {};
        for (auto namedExpress : namedExpressCtxVec) {
            expressVector.push_back(visitNamedExpression(namedExpress).as<SqlExpression>());
        }
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
};
