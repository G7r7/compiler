struct token {
    int type;
    int value;
    int line;
};

enum Tokens {
    tok_cst,
    tok_identificateur,
    tok_if,
    tok_parenthese_gauche,
    tok_parenthese_droite,
    tok_plus,
    tok_point_virgule,
    tok_eof
};