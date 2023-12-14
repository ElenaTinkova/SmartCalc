#include "mainwindow.h"

#include <QPixmap>

#include "deposit.h"
#include "form.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QPixmap picture(":/hello_puppy.jpeg");
  int wP = ui->label->width();
  int hP = ui->label->height();
  ui->label->setPixmap(picture.scaled(wP, hP, Qt::KeepAspectRatio));

  connect(ui->but_0, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->but_1, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->but_2, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->but_3, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->but_4, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->but_5, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->but_6, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->but_7, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->but_8, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->but_9, SIGNAL(released()), this, SLOT(NumPressed()));

  connect(ui->plus, SIGNAL(released()), this, SLOT(Operations()));
  connect(ui->minus, SIGNAL(released()), this, SLOT(Operations()));
  connect(ui->multiply, SIGNAL(released()), this, SLOT(Operations()));
  connect(ui->mod, SIGNAL(released()), this, SLOT(Operations()));
  connect(ui->lBrace, SIGNAL(released()), this, SLOT(Operations()));
  connect(ui->rBrace, SIGNAL(released()), this, SLOT(Operations()));

  connect(ui->f_sin, SIGNAL(released()), this, SLOT(FuncsPressed()));
  connect(ui->f_cos, SIGNAL(released()), this, SLOT(FuncsPressed()));
  connect(ui->f_tan, SIGNAL(released()), this, SLOT(FuncsPressed()));
  connect(ui->f_asin, SIGNAL(released()), this, SLOT(FuncsPressed()));
  connect(ui->f_acos, SIGNAL(released()), this, SLOT(FuncsPressed()));
  connect(ui->f_atan, SIGNAL(released()), this, SLOT(FuncsPressed()));
  connect(ui->f_ln, SIGNAL(released()), this, SLOT(FuncsPressed()));
  connect(ui->f_log, SIGNAL(released()), this, SLOT(FuncsPressed()));

  connect(ui->backspace, SIGNAL(released()), this, SLOT(BackspaceDeletion()));
  connect(ui->clear, SIGNAL(released()), this, SLOT(ClearAllDeletion()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::NumPressed() {
  QPushButton *bttn = (QPushButton *)sender();
  QString newExpression;
  if (ui->result_display->text() == '0') {
    newExpression = bttn->text();
  } else if (!ui->result_display->text().endsWith('x')) {
    newExpression = ui->result_display->text() + bttn->text();
  } else {
    newExpression = ui->result_display->text();
  }
  ui->result_display->setText(newExpression);
}

void MainWindow::FuncsPressed() {
  QPushButton *func = (QPushButton *)sender();
  QString all_numbers;
  if (ui->result_display->text() == '0') {
    all_numbers = func->text() + '(';
  } else {
    all_numbers = (ui->result_display->text() + func->text() + "(");
  }
  ui->result_display->setText(all_numbers);
}

void MainWindow::BackspaceDeletion() {
  QString resultNow = ui->result_display->text();
  int check = resultNow.size() - 1;
  if (check == 0) {
    ui->result_display->setText((QString)'0');
  } else {
    if (resultNow.endsWith("sqrt(") || resultNow.endsWith("acos(") ||
        resultNow.endsWith("asin(") || resultNow.endsWith("atan("))
      resultNow.chop(5);
    else if (resultNow.endsWith("sin(") || resultNow.endsWith("cos(") ||
             resultNow.endsWith("tan(") || resultNow.endsWith("log("))
      resultNow.chop(4);
    else if (resultNow.endsWith("ln(") || resultNow.endsWith("mod") ||
             resultNow.endsWith("inf") || resultNow.endsWith("nan"))
      resultNow.chop(3);
    else if (resultNow.endsWith("input")) {
      resultNow.chop(13);
    } else
      resultNow.chop(1);
    if (resultNow == "")
      ui->result_display->setText((QString)'0');
    else
      ui->result_display->setText(resultNow);
  }
  if (ui->expression_display->text().size() > 0 &&
      (resultNow.size() == 0 || check == 0))
    ui->expression_display->clear();
}

void MainWindow::ClearAllDeletion() {
  ui->result_display->clear();
  ui->expression_display->clear();
  ui->result_display->setText((QString)'0');
}

void MainWindow::Operations() {
  QPushButton *button = (QPushButton *)sender();

  QString new_display = ui->result_display->text();
  QString bttnName = button->text();

  if (new_display == "0" && (bttnName == "-" || bttnName == "(")) {
    new_display = bttnName;
  } else {
    if ((bttnName != "(" && bttnName != ")" && bttnName != "-" &&
         !new_display.endsWith(bttnName) &&
         (new_display[new_display.size() - 1].isDigit())) ||
        new_display.endsWith('x') || new_display.endsWith(')')) {
      new_display += bttnName;
    } else if (bttnName == "(" || bttnName == ")" ||
               (bttnName == "-" && !new_display.endsWith('-'))) {
      new_display += bttnName;
    }
  }
  ui->result_display->setText(new_display);
}

void MainWindow::on_divide_released() {
  QString new_display = ui->result_display->text();

  if ((new_display[new_display.size() - 1].isDigit() ||
       new_display.endsWith('x') || new_display.endsWith(')')) &&
      !new_display.endsWith("/")) {
    ui->result_display->setText(new_display += "/");
  }
}

void MainWindow::on_f_scale_released() {
  QString new_display = ui->result_display->text();
  if (!new_display.endsWith("^")) {
    ui->result_display->setText(new_display += "^");
  }
}

void MainWindow::on_f_sqrt_released() {
  QString new_display = ui->result_display->text();

  if (new_display == '0') {
    ui->result_display->setText("sqrt(");
  } else {
    new_display += "sqrt(";
    ui->result_display->setText(new_display);
  }
}

void MainWindow::on_dot_released() {
  QString new_display = ui->result_display->text();
  if (!new_display.endsWith(".") &&
      new_display[new_display.size() - 1].isDigit()) {
    ui->result_display->setText(new_display += ".");
  }
}

void MainWindow::on_val_X_released() {
  QString new_display = ui->result_display->text();
  if ((!new_display[new_display.size() - 1].isDigit() &&
       !new_display.endsWith("x")) &&
      !(new_display.size() - 1 == 0 && new_display == "0")) {
    ui->result_display->setText(new_display += "x");
  } else if (new_display.size() - 1 == 0 && new_display == "0") {
    ui->result_display->setText("x");
  }
}

void MainWindow::on_equals_released() {
  if (ui->result_display->text().size() == 0)
    ui->result_display->setText("Invalid input");
  else {
    QString new_display = ui->result_display->text() + '=';
    if (new_display.endsWith("==")) new_display.chop(1);
    ui->result_display->setText(new_display);
    ui->expression_display->setText(new_display);
    new_display.chop(1);

    QString valueX = ui->x_val->text();

    QByteArray bit_string = new_display.toLocal8Bit();
    char *stringForC = bit_string.data();
    char stringAfterValidation[256] = {0};
    int error = string_validation(stringForC, stringAfterValidation);
    if (error) {
      ui->result_display->setText("Invalid input");
    } else {
      if (new_display.contains('x')) {
        if ((!valueX.toDouble() || valueX == "") && valueX != "0")
          ui->result_display->setText("Invalid input");
        else {
          double x_val = valueX.toDouble();
          double res = calculations(stringAfterValidation, x_val);
          ui->result_display->setText(QString::number(res, 'g', 16));
        }
      } else {
        double res = calculations(stringAfterValidation, 0);
        ui->result_display->setText(QString::number(res, 'g', 16));
      }
    }
  }
}

void MainWindow::on_graph_released() {
  form = new Form;
  form->show();
  connect(this, &MainWindow::signalSecondScreen, form, &Form::getExpression);
  emit signalSecondScreen(ui->result_display->text());
}

void MainWindow::on_actionCredit_triggered() {
  credit = new Credit;
  credit->show();
}

void MainWindow::on_actionDeposit_triggered() {
  Deposit wind;
  wind.setModal(true);
  wind.exec();
}
