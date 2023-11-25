#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

extern "C"{
#include "../back/data_validation.h"
#include "../back/stack.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void NumPressed();
    void Operations();
    void FuncsPressed();
    void BackspaceDeletion();
    void ClearAllDeletion();
    void on_divide_released();
    void on_f_scale_released();
    void on_f_sqrt_released();
    void on_dot_released();
    void on_val_X_released();
};
#endif // MAINWINDOW_H
