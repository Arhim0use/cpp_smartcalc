#include "creditwindow.h"
#include "ui_creditwindow.h"

CreditWindow::CreditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditWindow)
{
    ui->setupUi(this);
    TableHead();
}

CreditWindow::~CreditWindow()
{
    delete ui;   
}

void CreditWindow::TableHead() {
  ui->tableWidget->setColumnCount(5);
  ui->tableWidget->setShowGrid(true);
  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tableWidget->clear();
  ui->tableWidget->setRowCount(0);
  QStringList headers;
  headers.append("Месяц");
  headers.append("Сумма платежа");
  headers.append("Основной долг");
  headers.append("Проценты");
  headers.append("Остаток долга");
  ui->tableWidget->setHorizontalHeaderLabels(headers);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
}

void CreditWindow::IncertInTable(double &overpayment, double &all_payment) {
    ui->tableWidget->clear();
    TableHead();
    bool is_year = ui->CB_period->currentIndex();
    int table_size = is_year ? period * 12 : period;
    for (int i = 0; i < table_size; i++) {
      overpayment += table[i][3];
      all_payment += table[i][1];
      ui->tableWidget->insertRow(i);
      ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(table[i][0])));
      ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(table[i][1], 'f', 2)));
      ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(table[i][2], 'f', 2)));
      ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(table[i][3], 'f', 2)));
      ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(table[i][4], 'f', 2)));
    }
    ui->label_all_payment->setText(QString::number(all_payment, 'f', 2));
    ui->label_overpayment->setText(QString::number(overpayment, 'f', 2));
    ui->label_m_payment->setText(QString::number(table[0][1], 'f', 2));
    if (ui->radioButton_diff->isChecked())
        ui->label_m_payment->setText(ui->label_m_payment->text() + " - " +
                                     QString::number(table[table_size - 1][1], 'f', 2));
}

void CreditWindow::on_pushButton_calculate_clicked() {
    table = nullptr;
    double amout = ui->DSB_credit_amount->value();
    double percent = ui->DSB_credit_percent->value();
    period = ui->SB_period->value();
    double overpayment = 0., all_payment = 0;
    if (ui->radioButton_ann->isChecked()) {
        controller_.AnnuityPaymentCalc(amout, percent, period, ui->CB_period->currentIndex());
    } else {
        controller_.DifferentiatedPaymentCalc(amout, percent, period, ui->CB_period->currentIndex());
    }
    table = controller_.GetCreditResultTable();
    if (table) {
        IncertInTable(overpayment, all_payment);
    }
}

void CreditWindow::ClearTable() {
    if (table) {
        for (int i = 0; i < period && table[i]; i++) {
            delete[] table [i];
            table[i] = nullptr;
        }
        if (table) delete[] table;
        table = nullptr;
    }
}

void CreditWindow::on_CB_period_currentIndexChanged(int index) {
    int period = ui->SB_period->value();
    if (index == 0) {
        ui->SB_period->setMaximum(60);
        ui->SB_period->setValue(period * 12);
    } else {
        ui->SB_period->setMaximum(5);
        ui->SB_period->setValue(period / 12);
    }
}

