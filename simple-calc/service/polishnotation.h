#ifndef POLISHNOTATION_H
#define POLISHNOTATION_H
#include<vector>
#include<queue>
#include<stack>
#include<QString>
#include<QVector>
/**
 * @file polish_notation.h
 * @brief This file contains functions for processing math expression from
 * string;
 */
enum PriorityClass{
    LOW_PRIORITY=2,
    AVG_PRIORITY=6,
    HIGH_PRIORITY=15,
    PRIORITY_CLASSES_COUNT
};
enum Priority{
    LEFT_BRACKET,
    PLUS,
    MINUS = 2,
    MULT,
    DIV,
    MOD,
    POW = 6,
    SIN,
    COS,
    TAN,
    ASIN,
    ACOS,
    ATAN,
    SQRT,
    LN,
    LOG = 15,
    U_MINUS,
    U_PLUS,
    OPER_COUNT
};

struct node {
    node(bool oper_flag,char oper_val, bool x_flag,double value_val){
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
    Stage(){}
    std::queue<node> polish;
    QVector<double> x;
    QVector<double> y;
    bool plot_enabled;
    int x_min;
    int x_max;
    int y_min;
    int y_max;
    int dot_count;
    double result;
};

class Evaluator
{

private:
    Stage stage;
    int oper_process(char* str, std::stack<char> &_stack, std::queue<node>& _queue, char is_last_oper);
/**
 * @brief Make queue copy with specified X value
 * @param src queue source.
 * @param dist queue destination.
 * @param current_x value of x;
 * @return value of popped node;
 */
    std::queue<node> copy_queue_without_x(std::queue<node> src, double current_x);
/**
 * @brief Evaluate expression from queue;
 * @param _queue queue source.
 * @param result pointer to result
 * @return status;
 */
    int  func_process(char* str, std::stack<char> &_stack, std::queue<node>& _queue);
    int  calc(std::queue<node> _queue, double* result,double x);
    void lasts_operation(std::stack<char> &_stack, std::queue<node> &_queue);
    int  digit_process(char* str, std::queue<node>& _queue);
public:
    Evaluator();

    /**
     * @brief Create stack and queue from string with reverse polish notation;
     *
     * @param str string with math expression.
     * @param _stack pointer to stack
     * @param _queue pointer to queue;
     * @return status. OK 1 if expression correct OK_WITH_X 2 if expression correct
     * and contains X. ERROR 0 smthing went wrong;
    */
    Evaluator& ToReversePolish(std::string str);
    Evaluator& PlotEnable(int x_min=-100,int y_min=-100,int x_max=100,int y_max=100,int accuracy=100);
    Stage& Calculate(double x);

};

#endif // POLISHNOTATION_H
