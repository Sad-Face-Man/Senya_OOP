#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*Начальные значения переменных*/

    curSelectedMaterial = materialPrice.none;

    /*Задаю текст label полей*/
    QString pushButton_result_text = "Рассчитать"; //надпись на кнопке для рассчёта результата
    ui->label_title->setText("Калькулятор цены пола в доме.");
    ui->label_length->setText("Длина комнаты (м.):");
    ui->label_width->setText("Ширина комнаты (м.):");
    ui->label_material->setText("Метериал:");
    ui->label_priceList->setText("Стоимосто материалов за 1 кв.м.:\n" +
                                 materialPrice.concret.second + ": " + QString::number(materialPrice.concret.first) + "р.\n" +
                                 materialPrice.linoleum.second + ": " + QString::number(materialPrice.linoleum.first) + "р.\n" +
                                 materialPrice.tile.second + ": " + QString::number(materialPrice.tile.first) + "р.\n" +
                                 materialPrice.parquet.second + ": " + QString::number(materialPrice.parquet.first) + "р.");
    ui->pushButton_result->setText(pushButton_result_text);
    ui->label_result->setText("Итог:");

    /*соединение сигналов-слотов*/
    connect(ui->comboBox_material, &QComboBox::currentTextChanged, this, &MainWindow::saveCurMaterial);
    connect(ui->pushButton_result, &QPushButton::clicked, this, &MainWindow::calculateResult);
    connect(ui->comboBox_material, &QComboBox::currentIndexChanged, this, &MainWindow::pointChangedDataStatus);
    connect(ui->lineEdit_length,   &QLineEdit::textChanged,         this, &MainWindow::pointChangedDataStatus);
    connect(ui->lineEdit_width,    &QLineEdit::textChanged,         this, &MainWindow::pointChangedDataStatus);
    connect(ui->pushButton_result, &QPushButton::clicked,           this, &MainWindow::pointChangedDataStatus);

}

MainWindow::PriceList::PriceList()
{
    none.first = std::numeric_limits<int>::quiet_NaN();
    none.second = "";
    concret.first = 502;
    concret.second = "Бетон";
    linoleum.first = 350;
    linoleum.second = "Линолеум";
    tile.first = 750;
    tile.second = "Плитка";
    parquet.first = 890;
    parquet.second = "Паркет";
}

void MainWindow::pointChangedDataStatus()
{
    QObject* source = sender();
    QString buttonText = "Рассчитать.";
    if(source->objectName() == "pushButton_result")
        ui->pushButton_result->setText(buttonText);
    else
        ui->pushButton_result->setText(buttonText + "*");
}
/*Сохраняет в переменную название и цену выбранного материала*/
void MainWindow::saveCurMaterial()
{
    QString selectedMaterialName = ui->comboBox_material->currentText();
    if(selectedMaterialName == "<Выберите метериал>")
        curSelectedMaterial = materialPrice.none;
    else
        if(selectedMaterialName == materialPrice.concret.second)
            curSelectedMaterial = materialPrice.concret;
        else
            if(selectedMaterialName == materialPrice.linoleum.second)
                curSelectedMaterial = materialPrice.linoleum;
            else
                if(selectedMaterialName == materialPrice.tile.second)
                    curSelectedMaterial = materialPrice.tile;
                else
                    if(selectedMaterialName == materialPrice.parquet.second)
                        curSelectedMaterial = materialPrice.parquet;
}
void MainWindow::calculateResult()
{

    if(ui->lineEdit_length->text() == "" ||
            ui->lineEdit_width->text() == "" ||
            this->curSelectedMaterial.second == "")
    {
        QMessageBox::critical(this, "Ошибка рассчёта.", "Сначала заполните все данные для рассчёта!");
    }
    else
        if(ui->lineEdit_length->text().toInt() <= 0 ||
           ui->lineEdit_width->text().toInt() <= 0)
            QMessageBox::warning(this, "Ошибка рассчёта!", "Укажите реальные размеры комнаты!");
        else
            {
                resultPrice = ui->lineEdit_length->text().toInt() *
                        ui->lineEdit_width->text().toInt() *
                        curSelectedMaterial.first;
                ui->label_result->setText("Итого:\nСтоимость пола: " + QString::number(resultPrice));
            }
}


MainWindow::~MainWindow()
{
    delete ui;
}

