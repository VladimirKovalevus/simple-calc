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
}
State EvalStringProcessor::getState(){
    return State(last_index,last_dot,last_zero,last_num);
}
std::string EvalStringProcessor::getLabelString(){ return label_string; }

void EvalStringProcessor::addToLabel(QString str) {
    if (last_index + str.size() >= size) {
        return;
    }
    if (last_dot == true && str[0] == '.') {
        return;
    }
    if (str[0] == '.') {
        last_dot = true;
    } else {
        last_dot = false;
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
void EvalStringProcessor::clear() {
    char a[256]={0};
    label_string =a;

    last_index=0;
}
