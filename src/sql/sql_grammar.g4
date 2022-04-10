grammar sql_grammar;
options { tokenVocab = sql_lexer; }

statement
    : query
    |