
#include "utils.hpp"

bool is_digit(char c) {
    if (c >= '0' && c <= '9') {
        return 1;
    }
    return 0;
}
int is_operator(char c) {
    int res = 0;
    switch (c) {
    case '+': {
        res = PLUS;
        break;
    }
    case '-': {
        res = MINUS;
        break;
    }
    case '/': {
        res = DIV;
        break;
    }
    case '*': {
        res = MULT;
        break;
    }
    case '^': {
        res = POW;
        break;
    }
    case '%': {
        res = MOD;
        break;
    }
    }
    return res;
}
int is_bracket(char c) {
    int res = 0;
    if (c == '(') {
        res = 1;
    }
    if (c == ')') {
        res = 2;
    }
    return res;
}
bool is_unar(char c) {
    if (c == '+' || c == '-') {
        return 1;
    }
    return 0;
}
int is_mod(const char* str) {
    int res = 0;
    if (str[0] == 'm' || str[0] == 'M') {
        if (str[1] == 'o' || str[1] == 'O') {
            if (str[2] == 'd' || str[2] == 'D') {
                res = MOD;
            }
        }
    }
    return res;
}
int is_cos(const char* str) {
    int res = 0;
    if (str[0] == 'c' || str[0] == 'C') {
        if (str[1] == 'o' || str[1] == 'O') {
            if (str[2] == 's' || str[2] == 'S') {
                res = COS;
            }
        }
    }
    return res;
}
int is_sin(const char* str) {
    int res = 0;
    if (str[0] == 's' || str[0] == 'S') {
        if (str[1] == 'i' || str[1] == 'I') {
            if (str[2] == 'n' || str[2] == 'N') {
                res = SIN;
            }
        }
    }
    return res;
}
int is_tan(const char* str) {
    int res = 0;
    if (str[0] == 't' || str[0] == 'T') {
        if (str[1] == 'a' || str[1] == 'A') {
            if (str[2] == 'n' || str[2] == 'N') {
                res = TAN;
            }
        }
    }
    return res;
}
int is_sqrt(const char* str) {
    int res = 0;
    if ((str[0] == 's' || str[0] == 'S') && (str[1] == 'q' || str[1] == 'Q') &&
        (str[2] == 'r' || str[2] == 'R') && (str[3] == 't' || str[3] == 'T')) {
        res = SQRT;
    }
    return res;
}
int is_log(const char* str) {
    int res = 0;
    if (str[0] == 'l' || str[0] == 'L') {
        if ((str[1] == 'o' || str[1] == 'O') && (str[2] == 'g' || str[2] == 'G')) {
            res = LOG;
        }
    }
    return res;
}
int is_ln(const char* str) {
    int res = 0;
    if (str[0] == 'l' || str[0] == 'L') {
        if (str[1] == 'n' || str[1] == 'N') {
            res = LN;
        }
    }
    return res;
}
int is_function(const char* str) {
    int res = 0;
    if (str[0] == 'a' || str[0] == 'A') {
        if (is_sin(&str[1])) {
            res = ASIN;
        } else if (is_cos(&str[1])) {
            res = ACOS;
        } else if (is_tan(&str[1])) {
            res = ATAN;
        }
    }
    if (is_cos(str)) {
        res = COS;
    } else if (is_sin(str)) {
        res = SIN;
    } else if (is_tan(str)) {
        res = TAN;
    } else if (is_sqrt(str)) {
        res = SQRT;
    } else if (is_log(str)) {
        res = LOG;
    } else if (is_ln(str)) {
        res = LN;
    } else if (is_mod(str)) {
        res = MOD;
    }
    return res;
}
