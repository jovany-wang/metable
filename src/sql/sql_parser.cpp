#include "src/sql/sql_parser.h"

#include <vector>
#include "SqlGrammarParser.h"
#include "SqlLexer.h"
#include "antlr4-runtime.h"

namespace metable {
    using namespace antlr4;
    using namespace std;

    UnaryExpr::UnaryExpr(Expr::ptr expr) : expr(expr) {};

    ColumnExpr::ColumnExpr(string columnName) : columnName(columnName) {};

    BinaryExpr::BinaryExpr(Expr::ptr left, Expr::ptr right) : left(left), right(right) {};

    StringLiteral::StringLiteral(string value) : value(value) {};

    BooleanLiteral::BooleanLiteral(bool value) : value(value) {};

    IntegerLiteral::IntegerLiteral(long value) : value(value) {};

    DecimalLiteral::DecimalLiteral(double value) : value(value) {};

    AliasExpr::AliasExpr(Expr::ptr expr, string alias) : expr(expr), alias(alias) {};

    SqlFrom::SqlFrom(string tableName) : tableName(tableName) {};

    SqlSelect::SqlSelect(vector<Expr::ptr> selectVec, SqlFrom from, Expr::ptr where)
            : selectVec(selectVec), from(from), where(where) {};

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
        vector<Expr::ptr> express_list = visitSelectClause(selectContext).as<vector<Expr::ptr>>();
        SqlFrom from = visitFromClause(fromClause).as<SqlFrom>();
        if (whereClause != nullptr) {
            Expr::ptr expr = visitWhereClause(whereClause).as<Expr::ptr>();
            return make_shared<SqlSelect>(SqlSelect{express_list, from, expr});
        } else {
            return make_shared<SqlSelect>(SqlSelect{express_list, from, std::make_shared<Expr>()});
        }
    }


}  // namespace metable