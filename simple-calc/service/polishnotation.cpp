#include "polishnotation.h"

#include <locale.h>
#include <math.h>
#include "utils.hpp"

double exec_bin(char oper, double a, double b) {
  double res = 0;
  switch (oper) {
    case PLUS:
      res = a + b;
      break;
    case MINUS:
      res = a - b;
      break;
    case MULT:
      res = a * b;
      break;
    case DIV:
      res = a / b;
      break;
    case MOD:
      res = fmod(a, b);
      break;
    case POW:
      res = pow(a, b);
      break;
  }
  return res;
}
double exec_unar(char oper, double a) {
  double res = 0;
  switch (oper) {
    case U_PLUS:
      res = a;
      break;
    case U_MINUS:
      res = -a;
      break;
    case SIN:
      res = sin(a);
      break;
    case COS:
      res = cos(a);
      break;
    case ASIN:
      res = asin(a);
      break;
    case ACOS:
      res = acos(a);
      break;
    case TAN:
      res = tan(a);
      break;
    case ATAN:
      res = atan(a);
      break;
    case SQRT:
      res = sqrt(a);
      break;
    case LN:
      res = log(a);
      break;
    case LOG:
      res = log10(a);
      break;
  }
  return res;
}
int is_unar_oper(char c) {
  int res = 0;
  if (c >= 7) res = 1;
  return res;
}

Evaluator::Evaluator() {}

Evaluator& Evaluator::ToReversePolish(std::string str) {
  int is_prev_oper = 0;
  std::stack<char> _stack;
  std::queue<node> _queue;
  for (int i = 0; str[i] != '\0' && i < 255; i++) {
    if (str[i] == ' ') {
      continue;
    }
    int func_shift = 0;
    int digit_shift = 0;
    if (str[i] == 'x' || str[i] == 'X') {
      _queue.push(node(0, 0, 1, 0));
      is_prev_oper = 0;
    } else if ((func_shift = func_process(&str[i], _stack, _queue) - 1) > 0) {
      is_prev_oper = 1;
      i += func_shift > 0 ? func_shift : 0;
    } else if (oper_process(&str[i], _stack, _queue, is_prev_oper)) {
      is_prev_oper = 1;
    } else {
      digit_shift = digit_process(&str[i], _queue) - 1;
      i += digit_shift > 0 ? digit_shift : 0;
      is_prev_oper = 0;
    }
  }
  lasts_operation(_stack, _queue);
  this->stage.polish = _queue;
  return *this;
}

int check_priority(char a, char b) {
  int res = 0;
  if (a == 0) {
    return 0;
  }
  if (a > AVG_PRIORITY) {
    res = (b <= AVG_PRIORITY);
  } else if (a > LOW_PRIORITY) {
    res = (b <= AVG_PRIORITY);
  } else if (a <= LOW_PRIORITY) {
    res = b <= LOW_PRIORITY;
  }
  return res;
}
int Evaluator::func_process(char* str, std::stack<char>& _stack,
                            std::queue<node>& _queue) {
  int res = is_function(str);
  int shift = 0;
  if (res) {
    while (!_stack.empty() && check_priority(_stack.top(), res)) {
      _queue.push(node(1, _stack.top(), 0, 0));
      _stack.pop();
    }
    _stack.push(res);
    switch (res) {
      case SQRT:
      case ATAN:
      case ASIN:
      case ACOS: {
        shift = 4;
        break;
      }
      case SIN:
      case COS:
      case TAN:
      case MOD:
      case LOG: {
        shift = 3;
        break;
      }
      case LN: {
        shift = 2;
        break;
      }
    }
  }
  return shift;
}
int Evaluator::digit_process(char* str, std::queue<node>& _queue) {
  int shift = 0;
  if (is_digit(str[0])) {
    double val;
    if (1 == sscanf(str, "%lf%n", &val, &shift)) {
      _queue.push(node(0, 0, 0, val));
    }
  }
  return shift;
}
int Evaluator::oper_process(char* str, std::stack<char>& _stack,
                            std::queue<node>& _queue, char is_last_oper) {
  int res = is_operator(str[0]);
  if (res) {
    if (res == PLUS && (is_last_oper || _queue.empty())) {
      res = U_PLUS;
    }
    if (res == MINUS && (is_last_oper || _queue.empty())) {
      res = U_MINUS;
    }
    while (!_stack.empty() && check_priority(_stack.top(), res)) {
      _queue.push(node(1, _stack.top(), 0, 0));
      _stack.pop();
    }

    _stack.push(res);

  } else {
    res = is_bracket(str[0]);
    if (res == 1) {
      _stack.push(LEFT_BRACKET);
    } else if (res == 2) {
      while (!_stack.empty() && !(LEFT_BRACKET == _stack.top())) {
        _queue.push(node(1, _stack.top(), 0, 0));
        _stack.pop();
      }
      if (!_stack.empty()) {
        _stack.pop();
      }
    }
  }

  return res;
}
void Evaluator::lasts_operation(std::stack<char>& _stack,
                                std::queue<node>& _queue) {
  while (!_stack.empty()) {
    _queue.push(node(1, _stack.top(), 0, 0));
    _stack.pop();
  }
}
Evaluator& Evaluator::PlotEnable(int x_min, int y_min, int x_max, int y_max,
                                 int accuracy) {
  stage.plot_enabled = true;
  stage.dot_count = accuracy;
  stage.x_max = x_max;
  stage.x_min = x_min;
  stage.y_max = y_max;
  stage.y_min = y_min;

  return *this;
}

Stage& Evaluator::Calculate(double x) {
  double a = 0;
  if (stage.plot_enabled) {
    std::vector<double> _x(stage.dot_count), _y(stage.dot_count);
    double step = fabs(stage.x_max - stage.x_min) / stage.dot_count;
    for (int i = 0; i < stage.dot_count; ++i) {
      _x[i] = stage.x_min + step * i;
      calc(stage.polish, &_y[i], _x[i]);
    }
    stage.x = _x;
    stage.y = _y;
  }
  calc(stage.polish, &a, x);
  stage.result = a;
  return stage;
}
int Evaluator::calc(std::queue<node> _queue, double* result, double x) {
  std::stack<double> _stack;
  double res = 0;
  while (!_queue.empty()) {
    node holder = _queue.front();
    _queue.pop();
    if (holder.is_x) {
      holder.is_x = 0;
      holder.value = x;
    }
    if (!holder.is_oper) {
      _stack.push(holder.value);
    } else {
      if (is_unar_oper(holder.oper)) {
        double val1;
        if (!_stack.empty()) {
          val1 = _stack.top();
          _stack.pop();
        } else {
          return -1;
        }
        res = exec_unar(holder.oper, val1);
        _stack.push(res);
      } else {
        double val1;
        double val2;
        if (!_stack.empty()) {
          val1 = _stack.top();
          _stack.pop();
        } else {
          return -1;
        }
        if (!_stack.empty()) {
          val2 = _stack.top();
          _stack.pop();
        } else {
          return -1;
        }
        res = exec_bin(holder.oper, val2, val1);
        _stack.push(res);
      }
    }
  }
  if (_stack.empty()) return -1;
  *result = _stack.top();
  return 0;
}
