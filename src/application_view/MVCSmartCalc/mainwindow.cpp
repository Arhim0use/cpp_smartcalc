#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  SetUpWindow();

  for (auto button : ui->GSingleSymbolButton->buttons()) {
    connect(button, SIGNAL(clicked()), this, SLOT(SingleSymbolClicked()));
  }

  for (auto button : ui->GFuncButton->buttons()) {
    connect(button, SIGNAL(clicked()), this, SLOT(FuncButtonClicked()));
  }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::SetUpWindow() {
  ui->graph_widget->yAxis->setRange(ui->DSB_max_y->value(),
                                    ui->DSB_min_y->value());
  ui->graph_widget->xAxis->setRange(ui->DSB_max_x->value(),
                                    ui->DSB_min_x->value());
  ui->Var_line->setText("1");
  ui->CalcLine->setFocus();
}

void MainWindow::SingleSymbolClicked() {
  QPushButton* button = (QPushButton*)sender();
  QWidget* activeWidget = QApplication::focusWidget();
  QLineEdit* activeLineEdit = qobject_cast<QLineEdit*>(activeWidget);

  if (activeLineEdit && activeLineEdit != ui->ResLine) {
    QString calc_str = activeLineEdit->text();
    if (button->text() == "mod") {
      calc_str += "%";
    } else {
      calc_str += button->text();
    }
    ui->pushButton_AC->setText("C");
    activeLineEdit->setText(calc_str);
  }
}

void MainWindow::FuncButtonClicked() {
  QPushButton* button = (QPushButton*)sender();
  QWidget* activeWidget = QApplication::focusWidget();
  QLineEdit* activeLineEdit = qobject_cast<QLineEdit*>(activeWidget);

  if (activeLineEdit && activeLineEdit != ui->ResLine &&
      activeLineEdit != ui->Var_line) {
    QString calc_str = activeLineEdit->text();
    calc_str += button->text() + "(";
    ui->pushButton_AC->setText("C");
    activeLineEdit->setText(calc_str);
  }
}

void MainWindow::on_pushButton_eq_clicked() {
  QString status = "Calc Line Status: ";
  QString res_str = "0";
  double result = 0.;
  ui->graph_widget->clearGraphs();
  controller_.SetVarX(ui->Var_line->text().toStdString());
  if (controller_.GetStatus() == 1) {
    status += "Error variable";
  } else {
    result = controller_.Calculate(ui->CalcLine->text().toStdString());
    if (controller_.GetStatus()) {
      status += "Error Plot Status: Error";
    } else {
      status += "Ok ";
    }
    if (X_InStr()) GrafPlotOnEqClicked(status);
  }
  res_str = res_str.number(result, 'g', 7);
  ui->ResLine->clear();
  ui->ResLine->setText(res_str);
  statusBar()->showMessage(status);
  ui->pushButton_AC->setText("C");
}

void MainWindow::GrafPlotOnEqClicked(QString& status_str) {
  double start_pos = ui->DSB_min_x->value();
  double end_pos = ui->DSB_max_x->value();
  int step_accuracy = ui->DotsSpinBox->value();
  ui->graph_widget->clearGraphs();
  status_str += "Plot Status: ";
  if (start_pos >= end_pos ||
      ui->DSB_min_y->value() >= ui->DSB_max_y->value()) {
    status_str += "Error the size of the graph output field";
  } else {
    status_str += "Ok";
    // auto my_graph =
    // controller_.GrafCalculation(step_accuracy, start_pos, end_pos);
    auto my_graph = controller_.GrafCalculation(
        ui->CalcLine->text().toStdString(), step_accuracy, start_pos, end_pos);
    PlotGraf(my_graph);
  }
}

bool MainWindow::X_InStr() {
  QString str = ui->CalcLine->text().toLower();
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == 'x') return true;
  }
  return false;
}

void MainWindow::PlotGraf(std::vector<std::vector<double>>& my_graph) {
  ui->graph_widget->xAxis->setRange(ui->DSB_max_x->value(),
                                    ui->DSB_min_x->value());
  ui->graph_widget->yAxis->setRange(ui->DSB_max_y->value(),
                                    ui->DSB_min_y->value());
  for (size_t i = 0; i < my_graph.at(0).size(); i++) {
    if (!my_graph.at(2).at(i)) {
      x.push_back(my_graph.at(0).at(i));
      y.push_back(my_graph.at(1).at(i));
    }
  }
  ui->graph_widget->addGraph();
  ui->graph_widget->graph(0)->addData(x, y);
  ui->graph_widget->replot();
  x.clear();
  y.clear();
}

void MainWindow::on_pushButton_del_clicked() {
  QString calc_str = ui->CalcLine->text();
  QChar last_sym = '\0';
  if (!calc_str.isEmpty()) last_sym = calc_str[calc_str.size() - 1];

  calc_str.resize(calc_str.size() - 1);
  if (!calc_str.isEmpty()) {
    QString oper = "0123456789.+-*/^xX%%eE()";

    int i = calc_str.size() - 1;
    QChar sym = calc_str[i];
    for (; i >= 0 && !oper.contains(calc_str[i]); i--) {
      sym = calc_str[i];
      calc_str.resize(calc_str.size() - 1);
    }
  }
  ui->CalcLine->setText(calc_str);
}

void MainWindow::on_pushButton_AC_clicked() {
  if (ui->CalcLine->text().isEmpty() && ui->Var_line->text().isEmpty() &&
      ui->ResLine->text().isEmpty())
    ui->pushButton_AC->setText("C");

  ui->CalcLine->clear();
  if (ui->pushButton_AC->text() == "AC") {
    ui->ResLine->clear();
    ui->Var_line->clear();
    ui->graph_widget->clearGraphs();
    ui->pushButton_AC->setText("C");
    statusBar()->showMessage("");
  } else {
    ui->pushButton_AC->setText("AC");
  }
}

void MainWindow::on_pushButton_credit_clicked() {
  credit_window = new CreditWindow(this);
  credit_window->show();
}
