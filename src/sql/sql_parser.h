#pragma once

#include <iostream>
#include <string>

#include "src/sql/anltr4/sql_grammar.inc/SqlGrammarBaseVisitor.h"

namespace metable {

    using namespace std;

    class Expr {
    };

// literal expression base class.
    class Literal : Expr {
    };

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
    class NullLiteral : Literal {
    };

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

    class ColumnExpr : Expr {
        string columnName;
    public:
        ColumnExpr(string columnName);
    };

    class AsteriskExpr : Expr {
    };

// define unary exprs

    class NotExpr : protected UnaryExpr {
    public:
        NotExpr(Expr expr) : UnaryExpr(expr) {};
    };

    class ParenExpr : protected UnaryExpr {
    public:
        ParenExpr(Expr expr) : UnaryExpr(expr) {};
    };

    class AndExpr : protected BinaryExpr {
    public:
        AndExpr(Expr left, Expr right) : BinaryExpr(left, right) {};
    };

    class OrExpr : protected BinaryExpr {
    public:
        OrExpr(Expr left, Expr right) : BinaryExpr(left, right) {};
    };

// TODO logicalPredicate expressions
// TODO arithmeticUnary expressions

// define arithmetic operators
    class PlusExpr : protected BinaryExpr {
    public:
        PlusExpr(Expr left, Expr right) : BinaryExpr(left, right) {};
    };

    class MinusExpr : protected BinaryExpr {
    public:
        MinusExpr(Expr left, Expr right) : BinaryExpr(left, right) {};
    };

    class MultiplyExpr : protected BinaryExpr {
    public:
        MultiplyExpr(Expr left, Expr right) : BinaryExpr(left, right) {};
    };

    class DivideExpr : protected BinaryExpr {
    public:
        DivideExpr(Expr left, Expr right) : BinaryExpr(left, right) {};
    };

    class ModExpr : protected BinaryExpr {
    public:
        ModExpr(Expr left, Expr right) : BinaryExpr(left, right) {};
    };

// define comparison operators
    class LtExpr : protected BinaryExpr {
    public:
        LtExpr(Expr left, Expr right) : BinaryExpr(left, right) {};
    };

    class LteExpr : protected BinaryExpr {
    public:
        LteExpr(Expr left, Expr right) : BinaryExpr(left, right) {};
    };

    class EqExpr : protected BinaryExpr {
    public:
        EqExpr(Expr left, Expr right) : BinaryExpr(left, right) {};
    };

    class GtExpr : protected BinaryExpr {
    public:
        GtExpr(Expr left, Expr right) : BinaryExpr(left, right) {};
    };

    class GteExpr : protected BinaryExpr {
    public:
        GteExpr(Expr left, Expr right) : BinaryExpr(left, right) {};
    };

    class NeqExpr : protected BinaryExpr {
    public:
        NeqExpr(Expr left, Expr right) : BinaryExpr(left, right) {};
    };

    class AliasExpr : Expr {
        Expr expr;
        string alias;

    public:
        AliasExpr(Expr expr, string alias);
    };

    class SqlFrom {
        string tableName;

    public:
        SqlFrom(string tableName);
    };

    class SqlStatement {
    };

    class SqlSelect : SqlStatement {
        vector<Expr> selectVec;
        SqlFrom from;
        Expr where;

    public:
        SqlSelect(vector<Expr> selectVec, SqlFrom from, Expr where);
    };

    class SqlParser {
    public:
        SqlSelect parse(string sql);
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
            for (auto namedExpress: namedExpressCtxVec) {
                exprVec.push_back(visitNamedExpression(namedExpress).as<Expr>());
            }
            return exprVec;
        }

        virtual antlrcpp::Any visitFromClause(
                SqlGrammarParser::FromClauseContext *ctx) override {
            string tableName = SqlGrammarBaseVisitor::visitIdentifier(ctx->identifier()).as<string>();
            return SqlFrom(tableName);
        }

        virtual antlrcpp::Any visitNamedExpression(
                SqlGrammarParser::NamedExpressionContext *ctx) override {
            Expr expr = visit(ctx->expression()).as<Expr>();
            if (ctx->identifier() != nullptr) {
                return AliasExpr(expr, ctx->identifier()->getText());
            } else {
                return AliasExpr(expr, "");
            }
        }

        // visit all boolean expression.
        virtual antlrcpp::Any visitLogicalNot(
                SqlGrammarParser::LogicalNotContext *ctx) override {
            Expr expr = visit(ctx->booleanExpression()).as<Expr>();
            return NotExpr(expr);
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
            Expr leftExpr = visit(ctx->left).as<Expr>();
            Expr rightExpr = visit(ctx->right).as<Expr>();
            if (ctx->AND() == nullptr) {
                return OrExpr{leftExpr, rightExpr};
            } else {
                return AndExpr(leftExpr, rightExpr);
            }
        }

        // todo visit arithmeticUnary
        virtual antlrcpp::Any visitArthmeticBinary(SqlGrammarParser::ArthmeticBinaryContext *ctx) override {
            Expr leftExpr = visit(ctx->left).as<Expr>();
            Expr rightExpr = visit(ctx->right).as<Expr>();
            if (ctx->arithmeticOperator()->PLUS() != nullptr) {
                return PlusExpr{leftExpr, rightExpr};
            } else if (ctx->arithmeticOperator()->MINUS() != nullptr) {
                return MinusExpr{leftExpr, rightExpr};
            } else if (ctx->arithmeticOperator()->ASTERISK() != nullptr) {
                return MultiplyExpr{leftExpr, rightExpr};
            } else if (ctx->arithmeticOperator()->SLASH() != nullptr) {
                return DivideExpr{leftExpr, rightExpr};
            } else { // mod expression.
                return ModExpr{leftExpr, rightExpr};
            }
        }

        virtual antlrcpp::Any visitComparisonBinary(SqlGrammarParser::ComparisonBinaryContext *ctx) override {
            Expr leftExpr = visit(ctx->left).as<Expr>();
            Expr rightExpr = visit(ctx->right).as<Expr>();
            if (ctx->comparisonOperator()->LT() != nullptr) {
                return LtExpr{leftExpr, rightExpr};
            } else if (ctx->comparisonOperator()->LTE() != nullptr) {
                return LteExpr{leftExpr, rightExpr};
            } else if (ctx->comparisonOperator()->EQ() != nullptr) {
                return EqExpr{leftExpr, rightExpr};
            } else if (ctx->comparisonOperator()->GT() != nullptr) {
                return GtExpr{leftExpr, rightExpr};
            } else if (ctx->comparisonOperator()->GTE() != nullptr) {
                return GteExpr{leftExpr, rightExpr};
            } else { // no equal expression.
                return NeqExpr{leftExpr, rightExpr};
            }
        }

        virtual antlrcpp::Any
        visitParenthesizedExpression(SqlGrammarParser::ParenthesizedExpressionContext *ctx) override {
            Expr expr = visit(ctx->expression()).as<Expr>();
            return ParenExpr{expr};
        }

        virtual antlrcpp::Any visitStar(SqlGrammarParser::StarContext *ctx) override {
            return AsteriskExpr{};
        }

        // parse constant expressions.
        virtual antlrcpp::Any visitNullLiteral(SqlGrammarParser::NullLiteralContext *ctx) override {
            return NullLiteral{};
        }

        virtual antlrcpp::Any visitStringLiteral(SqlGrammarParser::StringLiteralContext *ctx) override {
            return StringLiteral{ctx->STRING_LITERAL()->getText()};
        }

        virtual antlrcpp::Any visitIntegerLiteral(SqlGrammarParser::IntegerLiteralContext *ctx) override {
            return IntegerLiteral{stol(ctx->INTEGER_LITERAL()->getText())};
        }

        virtual antlrcpp::Any visitDecimalLiteral(SqlGrammarParser::DecimalLiteralContext *ctx) override {
            return DecimalLiteral(stod(ctx->DECIMAL_LITERAL()->getText()));
        }

        virtual antlrcpp::Any visitBooleanValue(SqlGrammarParser::BooleanValueContext *ctx) override {
            if (ctx->TRUE() != nullptr) {
                return BooleanLiteral{true};
            } else {
                return BooleanLiteral{false};
            }
        }

        virtual antlrcpp::Any visitColumnIdentifier(SqlGrammarParser::ColumnIdentifierContext *ctx) override {
            string columnName = SqlGrammarBaseVisitor::visitIdentifier(ctx->identifier()).as<string>();
            return ColumnExpr{columnName};
        }

        virtual antlrcpp::Any visitIdentifier(SqlGrammarParser::IdentifierContext *ctx) override {
            if (ctx->IDENTIFIER() != nullptr) {
                return ctx->IDENTIFIER()->getText();
            } else {
                return ctx->BACKQUOTED_IDENTIFIER()->getText();
            }
        }
    };

}  // namespace metable
