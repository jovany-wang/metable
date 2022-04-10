lexer grammar sql_lexer;

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
BETWEEN: 'BETWEEN';
COLUMN: 'COLUMN';
COMMENT: 'COMMENT';
CREATE: 'CREATE';
DATABASE: 'DATABASE';
DATABASES: 'DATABASES';
DELETE: 'DELETE';
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
NULL: 'NULL';
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

LT: '>';
LTE: '>=';
EQ: '=';
ET: '<';
EQT: '<=';
NEQ: '!=';

PLUS: '+';
MINUS: '-';
ASTERISK: '*';
SLASH: '/';
PERCENT: '%';

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