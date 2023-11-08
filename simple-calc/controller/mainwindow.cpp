#include "mainwindow.h"
#include "../ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setlocale(LC_NUMERIC, "C");
    ui->setupUi(this);
    ui->plot->addGraph();
    connect(ui->digits, SIGNAL(buttonClicked(QAbstractButton*)), this,
            SLOT(digit_pressed(QAbstractButton*)));
    connect(ui->brackets, SIGNAL(buttonClicked(QAbstractButton*)), this,
            SLOT(bracket_pressed(QAbstractButton*)));
    connect(ui->pushButton_dot, SIGNAL(pressed()), this, SLOT(dot_pressed()));
    connect(ui->pushButton_equal, SIGNAL(pressed()), this, SLOT(eval()));
    connect(ui->pushButton_backspace, SIGNAL(pressed()), this,
            SLOT(backspace_pressed()));
    connect(ui->pushButton_clear, SIGNAL(pressed()), this, SLOT(clear_pressed()));
    connect(ui->operators, SIGNAL(buttonClicked(QAbstractButton*)), this,
            SLOT(oper_pressed(QAbstractButton*)));
    connect(ui->functions, SIGNAL(buttonClicked(QAbstractButton*)), this,
            SLOT(function_pressed(QAbstractButton*)));
    connect(ui->pushButton_x, SIGNAL(pressed()), this, SLOT(press_x()));
    connect(ui->credit_but, SIGNAL(pressed()), this, SLOT(credit_calc()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::press_x() {
    ControlNode::getControlNode().addToLabel(QString("x"));
    ui->mainLabel->setText(ControlNode::getControlNode().getLabelString());
}
void MainWindow::credit_calc() {
    std::pair<QStringList,double> ansDiff = ControlNode::getControlNode().diffCredit(ui->sum->value(),
                                                        ui->duration->value(),
                                                        ui->percent->value());

    double annPay= ControlNode::getControlNode().annCredit(ui->sum->value(),
                                                            ui->percent->value(),
                                                            ui->duration->value());

    ui->back_sum->setText(QString::number(annPay * ui->duration->value()));
    ui->overkill->setText(QString::number(annPay * ui->duration->value() - ui->sum->value()));
    ui->month_pay->setText(QString::number(annPay));
    \

    ui->diff_over->setText(QString::number(ansDiff.second - ui->sum->value()));
    ui->diff_sum->setText(QString::number(ansDiff.second));
    ui->diff_pay->clear();
    ui->diff_pay->addItems(ansDiff.first);
}
void MainWindow::keyPressEvent(QKeyEvent* event) {
    if(event->key()>='0'&&event->key()<='9'){
        ControlNode::getControlNode().addToLabel(event->text());
    }else{
        switch (event->key()) {
        case Qt::Key_Comma:
            ControlNode::getControlNode().addToLabel(".");
            break;
        case Qt::Key_Minus:
            ControlNode::getControlNode().addToLabel("-");
            break;
        case Qt::Key_Plus:
            ControlNode::getControlNode().addToLabel("+");
            break;
        case Qt::Key_Slash:
            ControlNode::getControlNode().addToLabel("/");
            break;
        case Qt::Key_Asterisk:
            ControlNode::getControlNode().addToLabel("*");
            break;
        case Qt::Key_Backspace:
            ControlNode::getControlNode().removeLastChar();
            break;
        case Qt::Key_BracketLeft:
            ControlNode::getControlNode().addToLabel("(");
            break;
        case Qt::Key_BracketRight:
            ControlNode::getControlNode().addToLabel(")");
            break;
        case Qt::Key_X:
            ControlNode::getControlNode().addToLabel("x");
            break;
        }
    }
    ui->mainLabel->setText(ControlNode::getControlNode().getLabelString());
}
void MainWindow::digit_pressed(QAbstractButton* btn) {
    ControlNode::getControlNode().addToLabel(btn->text());
    ui->mainLabel->setText(ControlNode::getControlNode().getLabelString());
}
void MainWindow::bracket_pressed(QAbstractButton* btn) {
    ControlNode::getControlNode().addToLabel(btn->text());
    ui->mainLabel->setText(ControlNode::getControlNode().getLabelString());
}
void MainWindow::dot_pressed() {
    ControlNode::getControlNode().addToLabel(QString("."));
    ui->mainLabel->setText(ControlNode::getControlNode().getLabelString());
}
void MainWindow::eval() {
    if(ControlNode::getControlNode().is_valid()){
        Evaluator evaBuilder =ControlNode::getControlNode().getEvalProcessor();
        evaBuilder = evaBuilder.ToReversePolish(ui->mainLabel->text().toStdString());
        if(ui->tabWidget->currentIndex()==0){
            evaBuilder = evaBuilder.PlotEnable(ui->x_min->value(),
                                               ui->y_min->value(),
                                               ui->x_max->value(),
                                               ui->y_max->value());
        }
        Stage answer = evaBuilder.Calculate(ui->doubleSpinBox->value());
        ui->answerLabel->setText(QString::number(answer.result));
        ui->plot->graph(0)->setData(answer.x,answer.y);
        ui->plot->xAxis->setLabel("x");
        ui->plot->yAxis->setLabel("y");
        ui->plot->xAxis->setRange(ui->x_min->value(),
                                  ui->x_max->value());
        ui->plot->yAxis->setRange(ui->y_min->value(),
                                  ui->y_max->value());
        ui->plot->replot();
    }else{
        ui->answerLabel->setText("ERR");
    }
}
void MainWindow::oper_pressed(QAbstractButton* btn) {
    ControlNode::getControlNode().addToLabel(btn->text());
    ui->mainLabel->setText(ControlNode::getControlNode().getLabelString());
}
void MainWindow::function_pressed(QAbstractButton* btn) {
    if (btn->text() != "mod") {
        ControlNode::getControlNode().addToLabel(btn->text() + "(");
    } else {
        ControlNode::getControlNode().addToLabel(btn->text());
    }
    ui->mainLabel->setText(ControlNode::getControlNode().getLabelString());
}
void MainWindow::backspace_pressed() {
    ControlNode::getControlNode().removeLastChar();
    ui->mainLabel->setText(ControlNode::getControlNode().getLabelString());
}

void MainWindow::clear_pressed() {
    ControlNode::getControlNode().clear();
    ui->mainLabel->setText(ControlNode::getControlNode().getLabelString());
    ui->answerLabel->setText(QString(""));
}


