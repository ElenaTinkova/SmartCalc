#include "form.h"

#include "ui_form.h"

Form::Form(QWidget *parent) : QWidget(parent), ui(new Ui::Form) {
  ui->setupUi(this);
  ui->x_min->setRange(-100.0, 100);
  ui->x_max->setRange(-100.0, 100);
  ui->graphics->xAxis->setTickLabelColor(QColor(79, 76, 121));
  ui->graphics->yAxis->setTickLabelColor(QColor(79, 76, 121));
  ui->graphics->xAxis->setBasePen(QColor(79, 76, 121));
  ui->graphics->yAxis->setBasePen(QColor(79, 76, 121));
  ui->graphics->xAxis->setTickPen(QColor(79, 76, 121));
  ui->graphics->yAxis->setTickPen(QColor(79, 76, 121));
  ui->graphics->xAxis->setSubTickPen(QColor(79, 76, 121));
  ui->graphics->yAxis->setSubTickPen(QColor(79, 76, 121));
}

Form::~Form() { delete ui; }

void Form::on_plot_btn_clicked() {
  if (ui->resultDisplay->text() == "") ui->resultDisplay->setText("Error");
  QVector<double> x, y;
  x.clear();
  y.clear();
  ui->graphics->clearGraphs();

  double xMin = (double)ui->x_min->value();
  double xMax = (double)ui->x_max->value();
  double h = 0.01;
  //double h = (xMax - xMin) * 0.001;

  QByteArray bit_string = ui->resultDisplay->text().toLocal8Bit();
  char *stringForC = bit_string.data();
  char stringAfterValidation[256] = {0};
  int error = string_validation(stringForC, stringAfterValidation);
  if (error) {
    ui->resultDisplay->setText("Invalid input");
  } else {
    for (double X = xMin; X <= xMax; X += h) {
      double res = calculations(stringAfterValidation, X);
      x.push_back(X);
      y.push_back(res);

      ui->graphics->addGraph();
      ui->graphics->graph(0)->setData(x, y);

      ui->graphics->xAxis->setRange(xMin, xMax);
      ui->graphics->yAxis->setRange(xMin, xMax);

      ui->graphics->setInteraction(QCP::iRangeZoom, true);
      ui->graphics->setInteraction(QCP::iRangeDrag, true);

      ui->graphics->graph(0)->setPen(QColor(168, 164, 244, 255));
      QPen graphPen = ui->graphics->graph(0)->pen();
      graphPen.setWidth(2);
      ui->graphics->graph(0)->setPen(graphPen);

      ui->graphics->replot();
    }
  }
}

void Form::getExpression(QString a) { ui->resultDisplay->setText(a); }

void Form::on_clear_plot_clicked() {
  ui->graphics->clearGraphs();
  ui->graphics->replot();
}
