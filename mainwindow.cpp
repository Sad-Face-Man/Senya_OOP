#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    buffer = 0;
    isNumInBuf = false;

    /*Говорим, что кнопки можно помечать, как checked*/
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_mult->setCheckable(true);
    ui->pushButton_devide->setCheckable(true);

    /*присоединяем сигналы отт кнопок к слоту мат. операций*/
    connect(ui->pushButton_plus,   SIGNAL(clicked()), this, SLOT(mathOperations()));
    connect(ui->pushButton_minus,  SIGNAL(clicked()), this, SLOT(mathOperations()));
    connect(ui->pushButton_mult,   SIGNAL(clicked()), this, SLOT(mathOperations()));
    connect(ui->pushButton_devide, SIGNAL(clicked()), this, SLOT(mathOperations()));
    /*кнопки удаления*/
    connect(ui->pushButton_C,  SIGNAL(clicked()), this, SLOT(fieldsClear()));
    connect(ui->pushButton_CE, SIGNAL(clicked()), this, SLOT(fieldsClear()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPushed(QPushButton* curButton = nullptr)
{
    /*Помечаем все кнопки, как непомеченные*/
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_mult->setChecked(false);
    ui->pushButton_devide->setChecked(false);

    if(curButton)
        curButton->setChecked(true);
}

void MainWindow::mathOperations()
{

    QPushButton* button = (QPushButton*)sender(); // создаем объект Qкнопки для дальнейшего запоминания нажатия на эту операцию..
    if(!isNumInBuf)
    {
        buffer = ui->inputLine->text().toDouble(); //записываем данные  из строки в буффер.
        ui->buffer_out->setText(QString::number(buffer));
        ui->inputLine->clear(); //очищаем строку ввода.
        isNumInBuf = true;
    }
    setPushed(button); //Запоминаем нажатую кнопку
    ui->mathSign_out->setText(button->text());

    lastOperation_text = QString::number(buffer) + ' ' + button->text() + ' '; //сохраняем текст текущей операции (1е число и знак)
    //ui->lastOperation->setText(lastOperation_text);
}

void MainWindow::fieldsClear()
{
    QPushButton* button = (QPushButton*)sender();


    ui->inputLine->clear();
    if(button->text() == "CE")
    {
        buffer = 0;
        isNumInBuf = false;
        setPushed();
        ui->buffer_out->clear();
        ui->mathSign_out->clear();
        ui->lastOperation_out->clear();
    }
}

void MainWindow::on_pushButton_equal_clicked()
{
    bool isError(false); //была ли ошибка, при выполнении операций, например, деление на ноль.
    if(isNumInBuf && ui->inputLine->text() != "") //если в буффере И во вхоной строке вообще есть числа
    {
       inNum = ui->inputLine->text().toDouble(); //временная переменная для хранениия чслового значения, введённого полльзователем.
        if(ui->pushButton_plus->isChecked())
        {
            buffer+= inNum;
            ui->pushButton_plus->setChecked(false);
            isError = false;
        }
        else if(ui->pushButton_minus->isChecked())
        {
            buffer-= inNum;
            ui->pushButton_minus->setChecked(false);
            isError = false;
        }
        else if(ui->pushButton_mult->isChecked())
        {
            buffer*= inNum;
            ui->pushButton_minus->setChecked(false);
            isError = false;
        }
        else if(ui->pushButton_devide->isChecked())
        {
            try
            {
                if(inNum == 0)
                    throw DevideByZero("На ноль делить нельзя!");
                buffer/= inNum;
                ui->pushButton_plus->setChecked(false);
                isError = false;

            }
            catch (DevideByZero& error)
            {
                isError = true;
                QMessageBox::critical(this, "Ошибка деления на ноль.", error.what());
            }

        }

        if(!isError)
        {
            lastOperation_text += QString::number(inNum) + " = " + QString::number(buffer);
            ui->lastOperation_out->setText(lastOperation_text);
        }

        setPushed(); //убираем фиксацию нажатия со всех кнопок мат. действий.
        ui->inputLine->clear();
        ui->mathSign_out->clear();
        ui->buffer_out->setText(QString::number(buffer));
    }
}

