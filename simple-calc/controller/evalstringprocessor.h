#ifndef EVALSTRINGPROCESSOR_H
#define EVALSTRINGPROCESSOR_H

#include <QString>

struct State{
    State(){}
    State(int _last_index, bool _last_dot,bool _last_zero,int _last_num)
    {
        last_index=_last_index;
        last_dot= _last_dot;
        last_zero= _last_zero;
        last_num= _last_num;
    }
    int  last_index;
    bool last_dot;
    bool last_zero;
    bool last_num;
};

class EvalStringProcessor{

public:
    EvalStringProcessor();
    void addToLabel(QString str);
    void removeLastChar();
    void clear();
    void setState(State state);
    std::string getLabelString();
    State getState();

private:
    int getLastIndex() { return last_index; }

    std::string label_string;

    const int size = 255;

    int last_index=0;
    bool last_dot = false;
    bool last_zero = false;
    bool last_num = false;
};

#endif  // EVALSTRINGPROCESSOR_H
