#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*Устанавливаем картинку*/
    QPixmap pcPreviewImg("C:/Users/arpoz/Desktop/Учёба/Четвёртый семестр/ООП/LW/OOP_semester_4_LW_2/Project/sources/pcPic.png");

    /*Посснение для пользователя*/
    startNote = "У данной конфигурации ПК можно указать комплектующие,которые вы хотите улучшить за дополнительную плату. \nВыберите комплектующие,которые вы хотите заменить.";


    /*устанавливаем значения для основных переменных*/
    /*цены*/
    price_main = 59999; //основной комп
    price_1 = 2799;     //корпус
    price_2 = 7000;     //мат.плата
    price_3 = 13999;    //процессор
    price_4 = 43786;    //видеокарта
    price_5 = 12499;    //оперативная память.
    price_6 = 399;      //провода.
    price_all = price_1 + price_2 + price_3 + price_4 + price_5 + price_6;

    /*Вывод основной информации на экран*/
    ui->picturePlace->setPixmap(pcPreviewImg); //изображение
    ui->StartNote_out->setText(startNote);     //пояснение для пользователей
    /*цены*/
    ui->price_1_out->setText(QString::number(price_1) + "р.");
    ui->price_2_out->setText(QString::number(price_2)+ "р.");
    ui->price_3_out->setText(QString::number(price_3)+ "р.");
    ui->price_4_out->setText(QString::number(price_4)+ "р.");
    ui->price_5_out->setText(QString::number(price_5)+ "р.");
    ui->price_6_out->setText(QString::number(price_6)+ "р.");

    /*присоединяем сигналы*/
    connect(ui->checkBox_1,   &QCheckBox::stateChanged, this, &MainWindow::clicked_checkBox_1);
    connect(ui->checkBox_2,   &QCheckBox::stateChanged, this, &MainWindow::clicked_checkBox_2);
    connect(ui->checkBox_3,   &QCheckBox::stateChanged, this, &MainWindow::clicked_checkBox_3);
    connect(ui->checkBox_4,   &QCheckBox::stateChanged, this, &MainWindow::clicked_checkBox_4);
    connect(ui->checkBox_5,   &QCheckBox::stateChanged, this, &MainWindow::clicked_checkBox_5);
    connect(ui->checkBox_6,   &QCheckBox::stateChanged, this, &MainWindow::clicked_checkBox_6);
    //connect(ui->checkBox_all, &QCheckBox::stateChanged, this, &MainWindow::clicked_checkBox_all);

    emit(MainWindow::resultPrice_out());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clicked_checkBox_1()
{
    if(ui->checkBox_1->isChecked())
        price_curAccessories += price_1;
    else
        price_curAccessories -= price_1;
    emit(MainWindow::resultPrice_out());
}
void MainWindow::clicked_checkBox_2()
{
    if(ui->checkBox_2->isChecked())
        price_curAccessories += price_2;
    else
        price_curAccessories -= price_2;
    emit(MainWindow::resultPrice_out());
}
void MainWindow::clicked_checkBox_3()
{
    if(ui->checkBox_3->isChecked())
        price_curAccessories += price_3;
    else
        price_curAccessories -= price_3;
    emit(MainWindow::resultPrice_out());
}
void MainWindow::clicked_checkBox_4()
{
    if(ui->checkBox_4->isChecked())
        price_curAccessories += price_4;
    else
        price_curAccessories -= price_4;
    emit(MainWindow::resultPrice_out());
}
void MainWindow::clicked_checkBox_5()
{
    if(ui->checkBox_5->isChecked())
        price_curAccessories += price_5;
    else
        price_curAccessories -= price_5;
    emit(MainWindow::resultPrice_out());
}
void MainWindow::clicked_checkBox_6()
{
    if(ui->checkBox_6->isChecked())
        price_curAccessories += price_6;
    else
        price_curAccessories -= price_6;
    emit(MainWindow::resultPrice_out());
}

void MainWindow::resultPrice_out()
{
    discount = 0;
    if(price_curAccessories == price_all)
        discount = price_all * 0.1;

    price_result = price_main + price_curAccessories - discount;
    QString str_mainPrice = "Цена без комплектующих:\t" + QString::number(price_main) + "р.\n";
    QString str_accessoriesPrice = "Цена комплектующих:\t" + QString::number(price_curAccessories) + "р.\n";
    QString str_withoutDiscount = "Сумма без учёта скидки:\t" + QString::number(price_main + price_curAccessories) + "р.\n";
    QString str_resultPrice = "Итого:\t" + QString::number(price_result) + "р.\n";
    QString str_discount = "Скидка на комплектующие 10%:\t" + QString::number(discount) + "р.\n";


    if(price_curAccessories != price_all)
    {
        ui->lbl_resultPrice->setText(str_mainPrice +
                                     str_accessoriesPrice +
                                     str_resultPrice);
    }
    else
    {
        ui->lbl_resultPrice->setText(str_mainPrice +
                                     str_accessoriesPrice +
                                     str_withoutDiscount +
                                     str_resultPrice +
                                     str_discount);
    }
}
