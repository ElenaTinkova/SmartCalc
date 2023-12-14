#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QDialog>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QGridLayout>

extern "C"{
#include "../back/extra_calcs.h"
}

namespace Ui {
class Deposit;
}

class Deposit : public QDialog
{
    Q_OBJECT

public:
    explicit Deposit(QWidget *parent = nullptr);
    ~Deposit();

private slots:
 void on_pushButton_calc_clicked();
 void on_pushButton_add_clicked();
 void on_pushButton_clear_clicked();

private:
    Ui::Deposit *ui;
};

#endif // DEPOSIT_H
