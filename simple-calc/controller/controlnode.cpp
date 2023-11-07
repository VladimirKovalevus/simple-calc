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
    if(ESP.addToLabel(str)){
        memento[ESP.getLastIndex()] = ESP.getState();
    }
}
void ControlNode::removeLastChar(){
    ESP.removeLastChar();
    ESP.setState(memento[ESP.getLastIndex()]);
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
    auto ans =CreditCalc::DiffCredit(body,duration,percent);
    QStringList payments;
    for(int i =0;i<ans.first.size();i++){
        payments.push_back(QString("Платеж №")+QString::number(i+1)+" "+QString::number(ans.first[i]));
    }
    return std::make_pair(payments,ans.second);
}
double ControlNode::annCredit(double body,double duration,double percent){
    return CreditCalc::AnnCredit(body,duration,percent);
}

