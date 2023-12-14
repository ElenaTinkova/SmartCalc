#include "credit.h"

#include <QStandardItem>
#include <QTableWidget>

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QWidget(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
  ui->doubleSpinBox_amount->setRange(1000, 60000000);
  ui->spinBox_months->setRange(1, 360);
  ui->doubleSpinBox_percent->setMinimum(1);
}

Credit::~Credit() { delete ui; }

void Credit::on_loanCalculation_clicked() {
  credit_input credit_data;
  credit_data.amount = ui->doubleSpinBox_amount->value();
  credit_data.percent = ui->doubleSpinBox_percent->value();
  credit_data.term = ui->spinBox_months->value();

  if (ui->annuityType->isChecked()) {
    credit_output result = annuity_calculations(credit_data);
    ui->paidAllPayment->setText(QString::number(result.total_payments, 'f', 2));
    ui->paidInterest->setText(
        QString::number(result.interest_overpayment, 'f', 2));
    ui->paidMonth->setText(QString::number(result.monthly_payment, 'f', 2));

  } else if (ui->differentiatedType->isChecked()) {
    QStandardItemModel *table = new QStandardItemModel();
    QStringList headers =
        QObject::tr("Monthly payment,Principal part,Interest part,Debt balance")
            .simplified()
            .split(",");

    table->setHorizontalHeaderLabels(headers);
    double debt = credit_data.amount;
    double principalPayment = credit_data.amount / credit_data.term;
    double monthlyPercent = credit_data.percent / 12 / 100;
    double totalOverpayment = 0.0;
    double totalPayments = 0.0;

    for (int i = 0; i < credit_data.term; i++) {
      double interestPayment = debt * monthlyPercent;
      totalOverpayment += interestPayment;
      double summaryPayment = principalPayment + interestPayment;
      debt -= principalPayment;

      QStandardItem *item =
          new QStandardItem(QString::number(summaryPayment, 'f', 2));
      QStandardItem *principal =
          new QStandardItem(QString::number(principalPayment, 'f', 2));
      QStandardItem *interest =
          new QStandardItem(QString::number(interestPayment, 'f', 2));
      QStandardItem *balanceDebt =
          new QStandardItem(QString::number(debt, 'f', 2));

      table->setItem(i, 0, item);
      table->setItem(i, 1, principal);
      table->setItem(i, 2, interest);
      table->setItem(i, 3, balanceDebt);
    }

    totalPayments = credit_data.amount + totalOverpayment;

    ui->tableCredit->setModel(table);
    ui->tableCredit->resizeColumnsToContents();
    ui->tableCredit->resizeRowsToContents();
    ui->paidAllPayment->setText(QString::number(totalPayments, 'f', 2));
    ui->paidInterest->setText(QString::number(totalOverpayment, 'f', 2));
    ui->paidMonth->setText("check the table");
  }
}
