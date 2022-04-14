grammar SqlGrammar;
options { tokenVocab = SqlLexer; }

statement
    : query
    ; 

query
    : selectClause fromClause whereClause?
    ;

selectClause
    : SELECT nameExpressionSeq
    ;

fromClause
    : FROM tableIdentifier
    ;

whereClause
    : WHERE
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
    : NOT booleanExpression
    | valueExpression predicate?
    | left=booleanExpression (AND | OR) right=booleanExpression
    | LEFT_PAREN booleanExpression RIGHT_PAREN
    ; 

valueExpression
    : (PLUS | MINUS | TILDE) valueExpression
    | left=valueExpression arithmeticOperator right=valueExpression
    | left=valueExpression comparisonOperator right=valueExpression
    | constant
    | ASTERISK
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
