#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    double price_main; //цена на основной товар.
    double price_1, price_2, price_3, price_4, price_5, price_6; //цены на комплектующие.
    double price_all; //цена всех комплектуюших.
    double price_curAccessories;
    double price_result; //итоговая цена.
    double discount;

    QString startNote; //текст пояснения для пользователя, что он тут вообще делает..

private slots:
    void resultPrice_out();
    void clicked_checkBox_1();
    void clicked_checkBox_2();
    void clicked_checkBox_3();
    void clicked_checkBox_4();
    void clicked_checkBox_5();
    void clicked_checkBox_6();
    //void clicked_checkBox_all();


};
#endif // MAINWINDOW_H
