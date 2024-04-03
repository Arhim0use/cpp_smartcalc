#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>

#include "../../controller/bank_calc_controller.h"

namespace Ui {
class CreditWindow;
}

class CreditWindow : public QDialog {
  Q_OBJECT

 public:
  explicit CreditWindow(QWidget *parent = nullptr);
  ~CreditWindow();

 private slots:
  void on_pushButton_calculate_clicked();

  void on_CB_period_currentIndexChanged(int index);

 private:
  Ui::CreditWindow *ui;
  s21::BankCalcController controller_;
  int period;
  double **table;

  void ClearTable();
  void TableHead();
  void IncertInTable(double &overpayment, double &all_payment);
};

#endif  // CREDITWINDOW_H
