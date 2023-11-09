#include "controlnode.h"

#include "../service/creditcalc.h"
ControlNode::ControlNode() {}

ControlNode& ControlNode::getControlNode() {
  static ControlNode instance;

  return instance;
}

void ControlNode::addToLabel(QString str) {
  if (ESP.addToLabel(str)) {
    memento[ESP.getLastIndex()] = ESP.getState();
  }
}
bool ControlNode::is_valid() { return ESP.validateString(); }
void ControlNode::removeLastChar() {
  ESP.removeLastChar();
  ESP.setState(memento[ESP.getLastIndex()]);
}
QString ControlNode::getLabelString() {
  return QString(ESP.getLabelString().c_str());
}
Evaluator ControlNode::getEvalProcessor() { return evaluator; }
void ControlNode::clear() {
  ESP.clear();
  cursor = 0;
}

std::pair<QStringList, double> ControlNode::diffCredit(double body,
                                                       double duration,
                                                       double percent) {
  auto ans = CreditCalc::DiffCredit(body, duration, percent);

  return std::make_pair(payments_convert(ans.first), ans.second);
}
QStringList ControlNode::payments_convert(std::vector<double> payments) {
  QStringList list;
  for (int i = 0; i < payments.size(); i++) {
    list.push_back(QString("Платеж №") + QString::number(i + 1) + " " +
                   QString::number(payments[i]));
  }
  return list;
}

double ControlNode::annCredit(double body, double duration, double percent) {
  return CreditCalc::AnnCredit(body, duration, percent);
}
