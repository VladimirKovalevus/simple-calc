#include "evalstringprocessor.h"

#include <QDebug>
#include <iostream>

#include "../service/utils.hpp"

EvalStringProcessor::EvalStringProcessor() { clear(); }

void EvalStringProcessor::setState(State state) {
  last_index = state.last_index;
  last_dot = state.last_dot;
  last_zero = state.last_zero;
  last_num = state.last_num;
  is_x = state.is_x;
  brackets = state.brackets;
  last_oper = state.last_oper;
}
State EvalStringProcessor::getState() {
  return State(last_index, last_dot, last_zero, last_num, last_oper, is_x,
               brackets);
}
std::string EvalStringProcessor::getLabelString() {
  return std::string(label_string);
}

bool EvalStringProcessor::addToLabel(QString str) {
  if (last_index + str.size() >= size) {
    return false;
  }
  bool res = true;
  if (label_string[last_index - 1] == ')' &&
      ((!is_operator(str[0].unicode()) && !is_mod(str.toStdString().c_str())) &&
       str[0] != ')')) {
    res = false;
  }
  if (res) {
    if (is_function(str.toStdString().c_str())) {
      if (str == "mod") {
        if (last_oper && !is_unar(str[0].unicode())) {
          res = false;
        } else {
          last_dot = false;
          last_zero = false;
          last_num = false;
          last_oper = true;
          is_x = false;
        }
      } else {
        if (last_num || is_x) {
          res = false;
        } else {
          last_dot = false;
          last_zero = false;
          last_num = false;
          last_oper = true;
          brackets++;
        }
      }

    } else if (is_operator(str[0].unicode())) {
      if (last_oper && !is_unar(str[0].unicode())) {
        res = false;
      } else {
        last_dot = false;
        last_zero = false;
        last_num = false;
        last_oper = true;
        is_x = false;
      }
    } else if (is_digit(str[0].unicode())) {
      if (is_x) {
        res = false;
      } else {
        last_zero = str[0] == '0';
        last_num = true;
        last_oper = false;
      }
    } else if (str[0] == 'x') {
      if (is_x || last_dot || last_num) {
        res = false;
      } else {
        last_dot = false;
        last_zero = str[0] == '0';
        last_num = true;
        last_oper = false;
        is_x = true;
      }
    } else if (str[0] == '.') {
      if (last_dot || is_x) {
        res = false;
      } else {
        if (!last_num) str = "0.";
        last_dot = true;
        last_num = true;
        last_oper = false;
      }
    } else if (str[0] == '(') {
      if (!last_oper) {
        res = false;
      } else {
        brackets++;
      }
    } else if (str[0] == ')') {
      if (brackets > 0 && (is_x || last_num)) {
        brackets--;
      } else {
        res = false;
      }
    }
  }
  if (res) {
    for (int i = 0; i < str.size(); i++, last_index++) {
      label_string[last_index] = str[i].unicode();
    }
  }
  return true;
}
void EvalStringProcessor::removeLastChar() {
  if (last_index == 0) {
    return;
  }
  int to_remove = 1;
  bool is_find = 0;
  bool is_prev_brack = label_string[last_index-1]=='(';

  if (last_index > 3) {
    if (label_string[last_index - 4-is_prev_brack] == 'a' ||
        label_string[last_index - 4-is_prev_brack] == 'A') {
      if (is_sin(&label_string[last_index - 3-is_prev_brack]) ||
          is_cos(&label_string[last_index - 3-is_prev_brack]) ||
          is_tan(&label_string[last_index - 3-is_prev_brack])) {
        to_remove = 4+is_prev_brack;
        is_find = true;
      }
    } else if (is_sqrt(&label_string[last_index - 4])) {
      to_remove = 4+is_prev_brack;
      is_find = true;
    }
  }

  if (last_index > 2 && !is_find) {
    if (is_sin(&label_string[last_index - 3-is_prev_brack]) ||
        is_cos(&label_string[last_index - 3-is_prev_brack]) ||
        is_tan(&label_string[last_index - 3-is_prev_brack]) ||
        is_mod(&label_string[last_index - 3-is_prev_brack]) ||
        is_log(&label_string[last_index - 3-is_prev_brack])) {
      to_remove = 3+is_prev_brack;
      is_find = true;
    }
  }

  if(!is_find &&
      last_index > 1 &&
      is_ln(&label_string[last_index - 2 - is_prev_brack])) {
    to_remove = 2+is_prev_brack;
  }

  for (int i = 0; i < to_remove && last_index>0 ; i++) {
    label_string[--last_index] = ' ';
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
    if (is_digit(label_string[i])) {
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
      if (!is_last_oper &&
          !(label_string[i] == 'm' && label_string[i + 1] == 'o')) {
        res = false;
        break;
      } else {
        switch (shift) {
          case LN: {
            shift = 2;
            break;
          }
          case LOG:
          case SIN:
          case COS:
          case TAN:
          case MOD: {
            shift = 3;
            break;
          }
          case ASIN:
          case ACOS:
          case ATAN:
          case SQRT: {
            shift = 4;
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
      if (!is_last_oper || is_last_brack || now_number) {
        res = false;
        break;
      } else {
        is_last_oper = 0;
        is_last_brack = 0;
      }
    }
  }
  if (is_last_oper) res = false;

  return res;
}
void EvalStringProcessor::clear() {
  for (int i = 0; i < size; i++) {
    label_string[i] = '\0';
  }
  label_string[255] = '\0';
  setState(State());
}
