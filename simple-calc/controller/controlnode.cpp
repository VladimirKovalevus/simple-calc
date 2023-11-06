#include "controlnode.h"
#include "../service/creditcalc.h"
ControlNode::ControlNode()
{

}

ControlNode& ControlNode::getControlNode(){
    static ControlNode instance;

    return instance;
}

void ControlNode::addToLabel(QString str){
    ESP.addToLabel(str);
}
void ControlNode::removeLastChar(){
    ESP.removeLastChar();
}
QString ControlNode::getLabelString(){
    return QString(ESP.getLabelString().c_str());
}
Evaluator ControlNode::getEvalProcessor(){
    return evaluator;
}
void ControlNode::clear(){
    ESP.clear();
    cursor =0;
}

std::pair<QStringList,double> ControlNode::diffCredit(double body,double duration,double percent){
    return CreditCalc::DiffCredit(body,duration,percent);
}
double ControlNode::annCredit(double body,double duration,double percent){
    return CreditCalc::AnnCredit(body,duration,percent);
}

