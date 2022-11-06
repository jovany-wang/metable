#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "src/sql/anltr4/sql_grammar.inc/SqlGrammarBaseVisitor.h"

namespace metable {

    using namespace std;

    class Expr {
    public:
        using ptr = std::shared_ptr<Expr>;
        virtual ~Expr() {}
    };

// literal expression base class.
    class Literal : public Expr {
    };

// unary expression base class.
    class UnaryExpr : public Expr {
    protected:
        Expr::ptr expr;

    public:
        UnaryExpr(Expr::ptr Expr);
    };

// binary expression base class.
    class BinaryExpr : public Expr {
    protected:
        Expr::ptr left;
        Expr::ptr right;

    public:
        BinaryExpr(Expr::ptr left, Expr::ptr right);
    };

// define structs for all Literal.
    class NullLiteral : public Literal {
    };

    class StringLiteral : public Literal {
        string value;

    public:
        StringLiteral(string value);
    };

    class BooleanLiteral : public Literal {
        bool value;

    public:
        BooleanLiteral(bool value);
    };

    class IntegerLiteral : public Literal {
        long value;

    public:
        IntegerLiteral(long value);
    };

    class DecimalLiteral : public Literal {
        double value;

    public:
        DecimalLiteral(double value);
    };

    class ColumnExpr : public Expr {
        string columnName;
    public:
        ColumnExpr(string columnName);
    };

    class AsteriskExpr : public Expr {
    };

// define unary exprs

    class NotExpr : public UnaryExpr {
    public:
        NotExpr(Expr::ptr expr) : UnaryExpr(expr) {};
    };

    class ParenExpr : public UnaryExpr {
    public:
        ParenExpr(Expr::ptr expr) : UnaryExpr(expr) {};
    };

    class AndExpr : public BinaryExpr {
    public:
        AndExpr(Expr::ptr left, Expr::ptr right) : BinaryExpr(left, right) {};
    };

    class OrExpr : public BinaryExpr {
    public:
        OrExpr(Expr::ptr left, Expr::ptr right) : BinaryExpr(left, right) {};
    };

// TODO logicalPredicate expressions
// TODO arithmeticUnary expressions

// define arithmetic operators
    class PlusExpr : public BinaryExpr {
    public:
        PlusExpr(Expr::ptr left, Expr::ptr right) : BinaryExpr(left, right) {};
    };

    class MinusExpr : public BinaryExpr {
    public:
        MinusExpr(Expr::ptr left, Expr::ptr right) : BinaryExpr(left, right) {};
    };

    class MultiplyExpr : public BinaryExpr {
    public:
        MultiplyExpr(Expr::ptr left, Expr::ptr right) : BinaryExpr(left, right) {};
    };

    class DivideExpr : public BinaryExpr {
    public:
        DivideExpr(Expr::ptr left, Expr::ptr right) : BinaryExpr(left, right) {};
    };

    class ModExpr : public BinaryExpr {
    public:
        ModExpr(Expr::ptr left, Expr::ptr right) : BinaryExpr(left, right) {};
    };

// define comparison operators
    class LtExpr : public BinaryExpr {
    public:
        LtExpr(Expr::ptr left, Expr::ptr right) : BinaryExpr(left, right) {};
    };

    class LteExpr : public BinaryExpr {
    public:
        LteExpr(Expr::ptr left, Expr::ptr right) : BinaryExpr(left, right) {};
    };

    class EqExpr : public BinaryExpr {
    public:
        EqExpr(Expr::ptr left, Expr::ptr right) : BinaryExpr(left, right) {};
    };

    class GtExpr : public BinaryExpr {
    public:
        GtExpr(Expr::ptr left, Expr::ptr right) : BinaryExpr(left, right) {};
    };

    class GteExpr : public BinaryExpr {
    public:
        GteExpr(Expr::ptr left, Expr::ptr right) : BinaryExpr(left, right) {};
    };

    class NeqExpr : public BinaryExpr {
    public:
        NeqExpr(Expr::ptr left, Expr::ptr right) : BinaryExpr(left, right) {};
    };

    class AliasExpr : public Expr {
        Expr::ptr expr;
        string alias;

    public:
        AliasExpr(Expr::ptr expr, string alias);
    };

    class SqlFrom {
        string tableName;

    public:
        SqlFrom(string tableName);
    };

    class SqlStatement {
    };

    class SqlSelect : SqlStatement {
        vector<Expr::ptr> selectVec;
        SqlFrom from;
        Expr::ptr where;

    public:
        SqlSelect(vector<Expr::ptr> selectVec, SqlFrom from, Expr::ptr where);
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
            vector<Expr::ptr> exprVec = {};
            for (auto namedExpress: namedExpressCtxVec) {
                exprVec.push_back(visitNamedExpression(namedExpress).as<Expr::ptr>());
            }
            return exprVec;
        }

        virtual antlrcpp::Any visitFromClause(
                SqlGrammarParser::FromClauseContext *ctx) override {
            string tableName = visitIdentifier(ctx->identifier()).as<string>();
            return SqlFrom(tableName);
        }

        virtual antlrcpp::Any visitNamedExpression(
                SqlGrammarParser::NamedExpressionContext *ctx) override {
            Expr::ptr expr = visit(ctx->expression()).as<Expr::ptr>();
            if (ctx->identifier() != nullptr) {
                return (Expr::ptr)std::make_shared<AliasExpr>(expr, ctx->identifier()->getText());
            } else {
                return (Expr::ptr)std::make_shared<AliasExpr>(expr, "");
            }
        }

        // visit all boolean expression.
        virtual antlrcpp::Any visitLogicalNot(
                SqlGrammarParser::LogicalNotContext *ctx) override {
            Expr::ptr expr = visit(ctx->booleanExpression()).as<Expr::ptr>();
            return (Expr::ptr)std::make_shared<NotExpr>(expr);
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
            Expr::ptr leftExpr = visit(ctx->left).as<Expr::ptr>();
            Expr::ptr rightExpr = visit(ctx->right).as<Expr::ptr>();
            if (ctx->AND() == nullptr) {
                return (Expr::ptr)std::make_shared<OrExpr>(leftExpr, rightExpr);
            } else {
                return (Expr::ptr)std::make_shared<AndExpr>(leftExpr, rightExpr);
            }
        }

        // todo visit arithmeticUnary
        virtual antlrcpp::Any visitArthmeticBinary(SqlGrammarParser::ArthmeticBinaryContext *ctx) override {
            Expr::ptr leftExpr = visit(ctx->left).as<Expr::ptr>();
            Expr::ptr rightExpr = visit(ctx->right).as<Expr::ptr>();
            if (ctx->arithmeticOperator()->PLUS() != nullptr) {
                return (Expr::ptr)std::make_shared<PlusExpr>(leftExpr, rightExpr);
            } else if (ctx->arithmeticOperator()->MINUS() != nullptr) {
                return (Expr::ptr)std::make_shared<MinusExpr>(leftExpr, rightExpr);
            } else if (ctx->arithmeticOperator()->ASTERISK() != nullptr) {
                return (Expr::ptr)std::make_shared<MultiplyExpr>(leftExpr, rightExpr);
            } else if (ctx->arithmeticOperator()->SLASH() != nullptr) {
                return (Expr::ptr)std::make_shared<DivideExpr>(leftExpr, rightExpr);
            } else { // mod expression.
                return (Expr::ptr)std::make_shared<ModExpr>(leftExpr, rightExpr);
            }
        }

        virtual antlrcpp::Any visitComparisonBinary(SqlGrammarParser::ComparisonBinaryContext *ctx) override {
            Expr::ptr leftExpr = visit(ctx->left).as<Expr::ptr>();
            Expr::ptr rightExpr = visit(ctx->right).as<Expr::ptr>();
            if (ctx->comparisonOperator()->LT() != nullptr) {
                return (Expr::ptr)std::make_shared<LtExpr>(leftExpr, rightExpr);
            } else if (ctx->comparisonOperator()->LTE() != nullptr) {
                return (Expr::ptr)std::make_shared<LteExpr>(leftExpr, rightExpr);
            } else if (ctx->comparisonOperator()->EQ() != nullptr) {
                return (Expr::ptr)std::make_shared<EqExpr>(leftExpr, rightExpr);
            } else if (ctx->comparisonOperator()->GT() != nullptr) {
                return (Expr::ptr)std::make_shared<GtExpr>(leftExpr, rightExpr);
            } else if (ctx->comparisonOperator()->GTE() != nullptr) {
                return (Expr::ptr)std::make_shared<GteExpr>(leftExpr, rightExpr);
            } else { // no equal expression.
                return (Expr::ptr)std::make_shared<NeqExpr>(leftExpr, rightExpr);
            }
        }

        virtual antlrcpp::Any
        visitParenthesizedExpression(SqlGrammarParser::ParenthesizedExpressionContext *ctx) override {
            Expr::ptr expr = visit(ctx->expression()).as<Expr::ptr>();
            return (Expr::ptr)std::make_shared<ParenExpr>(expr);
        }

        virtual antlrcpp::Any visitStar(SqlGrammarParser::StarContext *ctx) override {
            return (Expr::ptr)std::make_shared<AsteriskExpr>();
        }

        // parse constant expressions.
        virtual antlrcpp::Any visitNullLiteral(SqlGrammarParser::NullLiteralContext *ctx) override {
            return (Expr::ptr)std::make_shared<NullLiteral>();
        }

        virtual antlrcpp::Any visitStringLiteral(SqlGrammarParser::StringLiteralContext *ctx) override {
            return (Expr::ptr)std::make_shared<StringLiteral>(ctx->STRING_LITERAL()->getText());
        }

        virtual antlrcpp::Any visitIntegerLiteral(SqlGrammarParser::IntegerLiteralContext *ctx) override {
            return (Expr::ptr)std::make_shared<IntegerLiteral>(stol(ctx->INTEGER_LITERAL()->getText()));
        }

        virtual antlrcpp::Any visitDecimalLiteral(SqlGrammarParser::DecimalLiteralContext *ctx) override {
            return (Expr::ptr)std::make_shared<DecimalLiteral>(stod(ctx->DECIMAL_LITERAL()->getText()));
        }

        virtual antlrcpp::Any visitBooleanValue(SqlGrammarParser::BooleanValueContext *ctx) override {
            if (ctx->TRUE() != nullptr) {
                return (Expr::ptr)std::make_shared<BooleanLiteral>(true);
            } else {
                return (Expr::ptr)std::make_shared<BooleanLiteral>(false);
            }
        }

        virtual antlrcpp::Any visitColumnIdentifier(SqlGrammarParser::ColumnIdentifierContext *ctx) override {
            string columnName = visitIdentifier(ctx->identifier()).as<string>();
            return (Expr::ptr)std::make_shared<ColumnExpr>(columnName);
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
