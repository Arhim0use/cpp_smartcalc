#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../../controller/controller.h"
#include "creditwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  void on_pushButton_eq_clicked();

  void on_pushButton_del_clicked();

  void on_pushButton_AC_clicked();

  void SingleSymbolClicked();
  void FuncButtonClicked();
  void PlotGraf(std::vector<std::vector<double>> &my_graf);

  void on_pushButton_credit_clicked();

 private:
  Ui::MainWindow *ui;
  CreditWindow *credit_window;
  s21::SmartCalcController controller_;
  QVector<double> x, y;

  void SetUpWindow();
  void BackspaceButtonClicked();
  void EqualButtonClicked();
  void CleanButtonClicked();
  void SingleSymbolButtonClicked();
  void GrafPlotOnEqClicked(QString &status_str);
  bool X_InStr();
};
#endif  // MAINWINDOW_H
