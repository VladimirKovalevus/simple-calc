#ifndef CONTROLNODE_H
#define CONTROLNODE_H
#include<memory>
#include<array>

#include"../service/polishnotation.h"
#include"evalstringprocessor.h"



class ControlNode
{
public:

    static ControlNode& getControlNode();

    void addToLabel(QString str);
    QString getLabelString();
    void removeLastChar();
    void clear();

    Stage eval();

private:

    ControlNode();

    ControlNode(const ControlNode& other);
    ControlNode (ControlNode&& other);
    ControlNode operator=(const ControlNode& other);
    ControlNode operator=(ControlNode&& other);


    Evaluator evaluator;
    EvalStringProcessor ESP;

    int cursor =0;
    std::array<State,100> memento;

};

#endif // CONTROLNODE_H
