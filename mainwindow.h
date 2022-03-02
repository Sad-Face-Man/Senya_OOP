#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox> //для работы со всплывающими окнами.
#include "devidebyzero.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT //макрос, внедряющий в отдельный файл всю необходимую инфориацию

private:
    Ui::MainWindow *ui;

    double buffer, inNum; //переменная- буффер для хранения числа, ушедшего из поля ввода и для хранения введённого числа.
    bool isNumInBuf; //Есть ли число в буффере.
    QString lastOperation_text; // переменная для хранения текста посследней операции.

    void setPushed(QPushButton*); //помеить кнопку, как нажтую (для запоминания мат. действия)

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void mathOperations(); //обработка сигналов от кнопом с мат. операциями.
    void fieldsClear();
    void on_pushButton_equal_clicked();
};
#endif // MAINWINDOW_H

