grammar SqlGrammar;
options { tokenVocab = SqlLexer; }

statement
    : query
    ;

query
    : selectClause fromClause whereClause? #queryStatement
    | subClause fromClause whereClause? #subStatement
    ;

selectClause
    : SELECT nameExpressionSeq
    ;

subClause
    : SUB namedExpression
    ;

fromClause
    : FROM tableIdentifier
    ;

whereClause
    : WHERE booleanExpression
    ; 

nameExpressionSeq
    : namedExpression (COMMA namedExpression)*
    ;

namedExpression
    : expression (AS alias=aliaIdentifier)?
    ;

expressionSeq
    : expression (COMMA expressionSeq)*
    ;

expression
    : booleanExpression
    ;


booleanExpression
    : NOT booleanExpression # logicalNot
    | valueExpression predicate? #logicalPredicate
    | left=booleanExpression (AND | OR) right=booleanExpression #logicalBinary
    ; 

valueExpression
    : (PLUS | MINUS | TILDE) valueExpression #arithmeticUnary
    | left=valueExpression arithmeticOperator right=valueExpression #arthmeticBinary
    | left=valueExpression comparisonOperator right=valueExpression #comparisonBinary
    | LEFT_PAREN expression RIGHT_PAREN #parenthesizedExpression
    | constant #constantValue
    | ASTERISK #star
    ;

predicate
    : NOT? kind=BETWEEN lower=valueExpression AND upper=valueExpression
    | NOT? kind=IN LEFT_PAREN expression (COMMA expression)* RIGHT_PAREN
    | NOT? kind=LIKE pattern=valueExpression
    | IS NOT? kind=NULL_
    | IS NOT? kind=(TRUE | FALSE)
    ;

constant
    : NULL_
    | STRING_LITERAL
    | INTEGER_LITERAL
    | DECIMAL_LITERAL
    | booleanValue
    ;

booleanValue
    : TRUE | FALSE
    ;

aliaIdentifier
    : IDENTIFIER
    | BACKQUOTED_IDENTIFIER
    ;

tableIdentifier
    : IDENTIFIER
    ;

comparisonOperator
    : LT | LTE | EQ | GT | GTE | NEQ
    ;

arithmeticOperator
    : PLUS | MINUS | ASTERISK | SLASH | PERCENT 
    ;
