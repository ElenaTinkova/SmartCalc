#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include  <QVector>
#include "qcustomplot.h"

extern "C"{
#include "../back/data_validation.h"
#include "../back/stack.h"
}

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_plot_btn_clicked();

    void on_clear_plot_clicked();

private:
    Ui::Form *ui;

public slots:
    void getExpression(QString a);
};

#endif // FORM_H
