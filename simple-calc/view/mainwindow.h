#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractButton>
#include <QEvent>
#include <QMainWindow>

#include "../controller/controlnode.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow* ui;
 private slots:
  void keyPressEvent(QKeyEvent* event) override;
  void digit_pressed(QAbstractButton* btn);
  void bracket_pressed(QAbstractButton* btn);
  void dot_pressed();
  void eval();
  void oper_pressed(QAbstractButton* btn);
  void function_pressed(QAbstractButton* btn);
  void backspace_pressed();
  void clear_pressed();
  void press_x();
  void credit_calc();
};
#endif  // MAINWINDOW_H
