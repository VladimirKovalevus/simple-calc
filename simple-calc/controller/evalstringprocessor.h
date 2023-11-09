#ifndef EVALSTRINGPROCESSOR_H
#define EVALSTRINGPROCESSOR_H

#include <QString>

struct State {
  State() {
    last_index = 0;
    last_dot = false;
    last_zero = false;
    last_num = false;
    last_oper = true;
    is_x = false;
    brackets = 0;
  }
  State(int _last_index, bool _last_dot, bool _last_zero, int _last_num,
        bool _last_oper, bool _is_x, int _brackets) {
    last_index = _last_index;
    last_dot = _last_dot;
    last_zero = _last_zero;
    last_num = _last_num;
    last_oper = _last_oper;
    brackets = _brackets;
    is_x = _is_x;
  }
  int last_index;
  bool last_dot;
  bool last_zero;
  bool last_num;
  bool last_oper;
  bool is_x;
  int brackets;
};

class EvalStringProcessor {
 public:
  EvalStringProcessor();
  bool addToLabel(QString str);
  void removeLastChar();
  void clear();
  void setState(State state);
  std::string getLabelString();
  State getState();
  int getLastIndex() { return last_index; }
  bool validateString();

 private:
  char label_string[256];
  const int size = 255;
  int last_index = 0;
  bool last_dot = false;
  bool last_zero = false;
  bool last_num = false;
  bool last_oper = true;
  bool is_x = false;
  int brackets = 0;
};

#endif  // EVALSTRINGPROCESSOR_H
