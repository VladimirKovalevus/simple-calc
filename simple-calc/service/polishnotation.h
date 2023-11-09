#ifndef POLISHNOTATION_H
#define POLISHNOTATION_H
#include <queue>
#include <stack>
#include <vector>
#include <string>
/**
 * @file polish_notation.h
 * @brief This file contains functions for processing math expression from
 * string;
 */

struct node {
  node(bool oper_flag, char oper_val, bool x_flag, double value_val) {
    is_oper = oper_flag;
    oper = oper_val;
    value = value_val;
    is_x = x_flag;
  }
  bool is_oper;
  bool is_x;
  char oper;
  double value;
};

struct Stage {
  Stage() {}
  std::queue<node> polish;
  std::vector<double> x;
  std::vector<double> y;
  bool plot_enabled;
  int x_min;
  int x_max;
  int y_min;
  int y_max;
  int dot_count;
  double result;
};

class Evaluator {
 private:
  Stage stage;
  int oper_process(char* str, std::stack<char>& _stack,
                   std::queue<node>& _queue, char is_last_oper);
  /**
   * @brief Evaluate expression from queue;
   * @param _queue queue source.
   * @param result pointer to result
   * @return status;
   */
  int func_process(char* str, std::stack<char>& _stack,
                   std::queue<node>& _queue);
  int calc(std::queue<node> _queue, double* result, double x);
  void lasts_operation(std::stack<char>& _stack, std::queue<node>& _queue);
  int digit_process(char* str, std::queue<node>& _queue);

 public:
  Evaluator();

  /**
   * @brief Create stack and queue from string with reverse polish notation;
   *
   * @param str string with math expression.
   */
  Evaluator& ToReversePolish(std::string str);
  Evaluator& PlotEnable(int x_min = -100, int y_min = -100, int x_max = 100,
                        int y_max = 100, int accuracy = 100);
  Stage& Calculate(double x=0);
};

#endif  // POLISHNOTATION_H
