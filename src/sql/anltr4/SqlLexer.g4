lexer grammar SqlLexer;

SEMICOLON: ';';
LEFT_PAREN: '(';
RIGHT_PAREN: ')';
COMMA: ',';
DOT: '.';
LEFT_BRACKET: '[';
RIGHT_BRACKET: ']';

// ========================
// == start of keywords list
// ========================
ADD: 'ADD';
ALTER: 'ALTER';
AND: 'AND';
AS: 'AS';
BETWEEN: 'BETWEEN';
COLUMN: 'COLUMN';
COMMENT: 'COMMENT';
CREATE: 'CREATE';
DATABASE: 'DATABASE';
DATABASES: 'DATABASES';
DELETE: 'DELETE';
DISTINCT: 'DISTINCT';
DROP: 'DROP';
FALSE: 'FALSE';
FROM: 'FROM';
IN: 'IN';
INSERT: 'INSERT';
INTO: 'INTO';
IS: 'IS';
KEY: 'KEY';
LIKE: 'LIKE';
NOT: 'NOT';
NULL_: 'NULL';
OR: 'OR';
PRIMARY: 'PRIMARY';
RENAME: 'RENAME';
SELECT: 'SELECT';
SET: 'SET';
SHOW: 'SHOW';
SUB: 'SUB';
TABLE: 'TABLE';
TABLES: 'TABLES';
TO: 'TO';
TRUE: 'TRUE';
UPDATE: 'UPDATE';
USE: 'USE';
VALUES: 'VALUES';
WHERE: 'WHERE';
// ===========================
// == end of keywords list.
// ===========================

// ===========================
// == start of column types list
// ===========================
BOOL: 'BOOL';
SHORT: 'SHORT';
INT: 'INT';
LONG: 'LONG';
FLOAT: 'FLOAT';
DOUBLE: 'DOUBLE';
DECIMAL: 'DECIMAL';
STRING: 'STRING';
DATE: 'DATE';
DATETIME: 'DATETIME';
// =============================
// == end of column types list
// =============================

LT: '<';
LTE: '<=';
EQ: '=';
GT: '>';
GTE: '>=';
NEQ: '!=';

PLUS: '+';
MINUS: '-';
ASTERISK: '*';
SLASH: '/';
PERCENT: '%';
TILDE: '~';

IDENTIFIER
    : (LETTER | DIGIT | '_')+
    ;

BACKQUOTED_IDENTIFIER
    : '`' ( ~'`' | '``' )* '`'
    ;

STRING_LITERAL
    : '\'' ( ~('\''|'\\') | ('\\' .) )* '\''
    | '"' ( ~('"'|'\\') | ('\\' .) )* '"'
    ;

INTEGER_LITERAL
    : DIGIT+
    ;

DECIMAL_LITERAL
    : DECIMAL_DIGITS
    ;

fragment LETTER
    : [A-Z]
    ;
fragment DIGIT
    : [0-9]
    ;

fragment DECIMAL_DIGITS
    : DIGIT+ '.' DIGIT+
    ;

WS
    : [ \r\n\t]+ -> channel(HIDDEN)
    ;