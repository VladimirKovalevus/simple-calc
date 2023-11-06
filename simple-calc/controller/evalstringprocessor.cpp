#include "evalstringprocessor.h"

#include <QDebug>
#include <iostream>
#include"../service/utils.hpp"

EvalStringProcessor::EvalStringProcessor() { clear(); }

void EvalStringProcessor::setState(State state){
    last_index = state.last_index;
    last_dot = state.last_dot;
    last_zero = state.last_zero;
    last_num = state.last_num;
    is_x = state.is_x;
    brackets = state.brackets;
    last_oper =state.last_oper;
}
State EvalStringProcessor::getState(){
    return State(last_index,last_dot,last_zero,last_num,last_oper,is_x,brackets);
}
std::string EvalStringProcessor::getLabelString(){ return std::string(label_string); }

void EvalStringProcessor::addToLabel(QString str) {
    if (last_index + str.size() >= size) {
        return;
    }
    if(is_function(str.toStdString().c_str())){
        if(str=="mod"){
            if(last_oper&&!is_unar(str[0].unicode())){
                return;
            }
            last_dot = false;
            last_zero = false;
            last_num = false;
            last_oper = true;
            is_x = false;
        }
        else{
            if(last_num||is_x) return;
            last_dot = false;
            last_zero = false;
            last_num = false;
            last_oper = true;
        }

    }else if(is_operator(str[0].unicode())){
        if(last_oper&&!is_unar(str[0].unicode())){
            return;
        }
        last_dot = false;
        last_zero = false;
        last_num = false;
        last_oper = true;
        is_x = false;
    }else if(is_digit(str[0].unicode())){
        if(is_x) return;
        last_zero = str[0]=='0';
        last_num=true;
        last_oper = false;
    }else if(str[0]=='x'){
        if(is_x||last_dot||last_num){
            return;
        }
        last_dot=false;
        last_zero = str[0]=='0';
        last_num=true;
        last_oper = false;
        is_x=true;
    }else if(str[0]=='.'){
        if(last_dot||is_x) return;
        if(!last_num) str ="0.";
        last_dot=true;
        last_num = true;
        last_oper = false;
    }

    for (int i = 0; i < str.size(); i++, last_index++) {
        label_string[last_index] = str[i].unicode();
    }
}
void EvalStringProcessor::removeLastChar() {
    if (last_index == 0) {
        return;
    }
    int to_remove = 1;
    bool is_find = 0;
    if(label_string[last_index-1]=='('){
        to_remove=0;
        label_string[--last_index]=' ';
    }
    if (last_index > 3) {
        if (label_string[last_index - 4] == 'a' ||
            label_string[last_index - 4] == 'A') {
            if (is_sin(&label_string[last_index - 3]) ||
                is_cos(&label_string[last_index - 3]) ||
                is_tan(&label_string[last_index - 3])) {
                to_remove = 4;
                is_find = true;
            }
        } else if (is_sqrt(&label_string[last_index - 4])) {
            to_remove = 4;
            is_find = true;
        }
    }
    if (last_index > 2 && !is_find) {
        if (is_sin(&label_string[last_index - 3]) ||
            is_cos(&label_string[last_index - 3]) ||
            is_tan(&label_string[last_index - 3])) {
            to_remove = 3;
            is_find = true;
        } else if (is_log(&label_string[last_index - 3])) {
            to_remove = 3;
            is_find = true;
        }
    }
    if (!is_find && last_index > 1 && is_ln(&label_string[last_index - 1])) {
        to_remove = 2;
    }

    for (int i = 0; i < to_remove; i++) {
        last_index--;
        label_string[last_index] = ' ';
    }
}

bool EvalStringProcessor::validateString() {
    int res = true;
    bool now_number = 0;
    int brackets = 0;
    bool is_last_oper = 1;
    bool dot_placed = 0;
    bool is_last_brack = 0;

    for (int i = 0; label_string[i] != '\0' && i < 255; i++) {
        if (label_string[i] == '(') {
            if (is_last_oper == 0) {
                res = false;
                break;
            } else {
                brackets++;
            }
        }
        if (label_string[i] == ')') {
            brackets--;
            is_last_brack = 1;
            if (brackets < 0) {
                res = false;
                break;
            }
        }
        if (label_string[i]) {
            if (is_last_brack) {
                res = false;
                break;
            }
            now_number = 1;
            is_last_oper = 0;
            is_last_brack = 0;
        }
        if (label_string[i] == '.') {
            if (now_number && dot_placed) {
                res = false;
                break;
            } else if (now_number) {
                dot_placed = 1;
            } else {
                res = false;
                break;
            }
        }
        if (is_operator(label_string[i])) {
            if (is_last_oper) {
                if ((label_string[i] == '+' || label_string[i] == '-')) {
                    if (!is_last_oper) {
                        is_last_oper = 1;
                    }
                } else {
                    res = false;
                    break;
                }
            } else {
                is_last_brack = 0;
                now_number = 0;
                is_last_oper = 1;
                dot_placed = 0;
            }
        }
        int shift = is_function(&label_string[i]);
        if (shift) {
            is_last_brack = 0;
            if (!is_last_oper && !(label_string[i] == 'm' && label_string[i + 1] == 'o')) {
                res = false;
                break;
            } else {
                switch (shift) {
                case LN: {
                    shift = 2;
                    break;
                }
                case LOG: {
                    shift = 3;
                    break;
                }
                case SIN: {
                    shift = 3;
                    break;
                }
                case COS: {
                    shift = 3;
                    break;
                }
                case TAN: {
                    shift = 3;
                    break;
                }
                case ASIN: {
                    shift = 4;
                    break;
                }
                case ACOS: {
                    shift = 4;
                    break;
                }
                case ATAN: {
                    shift = 4;
                    break;
                }
                case SQRT: {
                    shift = 4;
                    break;
                }
                case MOD: {
                    shift = 3;
                    break;
                }
                }
                i += shift - 1;
                now_number = 0;
                is_last_oper = 1;
                dot_placed = 0;
            }
        }

        if (label_string[i] == 'x') {
            if (!is_last_oper || is_last_brack||now_number) {
                res = false;
                break;
            } else {
                is_last_oper = 0;
                is_last_brack = 0;
            }
        }
    }

    return res;
}
void EvalStringProcessor::clear() {
    for (int i = 0; i < size; i++) {
        label_string[i] = ' ';
    }
    label_string[255] = '\0';
    setState(State());
}
