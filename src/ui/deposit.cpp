#include "deposit.h"

#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent) : QDialog(parent), ui(new Ui::Deposit) {
  ui->setupUi(this);
  ui->tableWidget_deposit->setColumnWidth(0, 113);
  ui->tableWidget_deposit->setColumnWidth(1, 140);
  ui->tableWidget_deposit->setColumnWidth(2, 140);
}

Deposit::~Deposit() { delete ui; }

void Deposit::on_pushButton_calc_clicked() {
  int is_error = 0;
  ui->label_error->clear();

  deposit_info *dep = (deposit_info *)calloc(1, sizeof(deposit_info));
  dep->input_summ = ui->doubleSpinBox_start_summ->value();
  dep->temp_of_placement = ui->spinBox_months->value();
  dep->percent = ui->doubleSpinBox_percent->value();
  dep->tax_rate = ui->doubleSpinBox_tax_rate->value();
  dep->capitalization_of_interest = ui->checkBox_cap->isChecked();

  int selectedIndex = ui->comboBox_payments->currentIndex();
  if (selectedIndex == 0)
    dep->frequency_of_payments = 1;
  else if (selectedIndex == 1)
    dep->frequency_of_payments = 3;
  else if (selectedIndex == 2)
    dep->frequency_of_payments = 6;
  else if (selectedIndex == 3)
    dep->frequency_of_payments = 12;

  // каждый месяц
  Month *months = (Month *)calloc(dep->temp_of_placement, sizeof(Month));
  int rows = ui->tableWidget_deposit->rowCount();

  for (int i = 0; i < rows && !is_error; i++) {
    QSpinBox *spinBox = (QSpinBox *)(ui->tableWidget_deposit->cellWidget(i, 0));
    int number_of_month = spinBox->value();
    if (number_of_month >= dep->temp_of_placement) {
      is_error = 1;
    } else {
      QDoubleSpinBox *item_plus =
          (QDoubleSpinBox *)(ui->tableWidget_deposit->cellWidget(i, 1));
      QDoubleSpinBox *item_minus =
          (QDoubleSpinBox *)(ui->tableWidget_deposit->cellWidget(i, 2));
      months[number_of_month - 1].plus_value = item_plus->value();
      months[number_of_month - 1].minus_value = item_minus->value();
    }
  }

  if (!is_error && deposit_calculation(dep, months)) {
    // добавляем результат расчетов в поля
    ui->label_summ_end->setText(QString::number(dep->result_summ, 'f', 2));
    ui->label_summ_percent->setText(
        QString::number(dep->accrued_interest, 'f', 2));
    ui->label_summ_tax->setText(QString::number(dep->tax_amount, 'f', 2));
  } else {
    ui->label_error->setText("Error");
  }

  free(dep);
  free(months);
}

void Deposit::on_pushButton_add_clicked() {
  int row = ui->tableWidget_deposit->rowCount();
  ui->tableWidget_deposit->insertRow(row);

  QSpinBox *spinBox = new QSpinBox();
  spinBox->setMaximum(ui->spinBox_months->value() - 1);
  spinBox->setMinimum(1);
  ui->tableWidget_deposit->setCellWidget(row, 0, spinBox);

  for (int col = 1; col <= 2; col++) {
    QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox();
    doubleSpinBox->setDecimals(2);
    doubleSpinBox->setSingleStep(100);
    doubleSpinBox->setMinimum(0);
    doubleSpinBox->setMaximum(100000000);
    doubleSpinBox->setGroupSeparatorShown(true);
    ui->tableWidget_deposit->setCellWidget(row, col, doubleSpinBox);
  }
}

void Deposit::on_pushButton_clear_clicked() {
  ui->label_summ_end->setText("0.00");
  ui->label_summ_percent->setText("0.00");
  ui->label_summ_tax->setText("0.00");
  ui->label_error->clear();
  ui->tableWidget_deposit->clearContents();

  int numRows = ui->tableWidget_deposit->rowCount();
  for (int row = numRows - 1; row >= 0; row--) {
    ui->tableWidget_deposit->removeRow(row);
  }
}
