grammar sql_grammar;
options { tokenVocab = sql_lexer; }

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
    | left=booleanExpression operator=AND right=booleanExpression
    | left=booleanExpression operator=OR right=booleanExpression
    | LEFT_PAREN booleanExpression RIGHT_PAREN
    ; 

valueExpression
    : 
    | operator=(PLUS | MINUS | TILDE) valueExpression
    | left=valueExpression operator=arithmeticOperator right=valueExpression
    | left=valueExpression operator=comparisonOperator right=valueExpression
    | constant
    | ASTERISK
    ;

predicate
    : NOT? kind=BETWEEN lower=valueExpression AND upper=valueExpression
    | NOT? kind=IN LEFT_PAREN expression (COMMA expression)* RIGHT_PAREN
    | NOT? kind=LIKE pattern=valueExpression
    | IS NOT? kind=NULL
    | IS NOT? kind=(TRUE | FALSE)
    ;

constant
    : NULL
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

predicateOperator
    : OR | AND | IN | NOT
    ;
