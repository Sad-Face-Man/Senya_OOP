#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /*Цены на материалы за 1 кв.м. в руб.*/
    struct PriceList
    {
        QPair<double, QString> none;
        QPair<double, QString> concret;
        QPair<double, QString> linoleum;
        QPair<double, QString> tile;
        QPair<double, QString> parquet;
        PriceList();
    };
    PriceList materialPrice;


private:
    Ui::MainWindow *ui;
    QPair<double, QString> curSelectedMaterial; //материал, который сейчас выбран
    double resultPrice;
public slots:
    void pointChangedDataStatus(); //добавляет или удаляет "*" в надписи на кнопке
    void calculateResult();
    void saveCurMaterial();
};
#endif // MAINWINDOW_H
