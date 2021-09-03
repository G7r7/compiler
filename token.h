#ifndef Token
#define Token

struct token {
    int type;
    int value;
    int line;
};

enum Tokens {
    tok_cst,
    tok_id,
    tok_plus,
    tok_minus,
    tok_times,
    tok_divide,
    tok_modulo,
    tok_bang,
    tok_address,
    tok_equals,
    tok_equals_to,
    tok_not_equals_to,
    tok_less_than,
    tok_less_or_equal,
    tok_more_than,
    tok_more_or_equal,
    tok_and,
    tok_or,
    tok_comma,
    tok_semi_colon,
    tok_int,
    tok_if,
    tok_else,
    tok_for,
    tok_while,
    tok_do,
    tok_break,
    tok_continue,
    tok_return,
    tok_left_parenthesis,
    tok_right_parenthesis,
    tok_left_bracket,
    tok_right_bracket,
    tok_left_curly,
    tok_right_curly,
    tok_eof,
    tok_error
};

#endif