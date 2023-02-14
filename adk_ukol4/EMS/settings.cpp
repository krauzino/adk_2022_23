#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    // Initialization
    iterDisplace1 = 500;
    iterDisplace2 = 500;
  //  dz = 10;

    // Set default values to line edits
    ui->lineEdit_IterDisplace1->setText(QString::number(iterDisplace1));
    ui->lineEdit_IterDisplace2->setText(QString::number(iterDisplace2));
  //  ui->lineEdit_3->setText(QString::number(dz));

}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_lineEdit_editingFinished()
{
    iterDisplace1 = ui->lineEdit_IterDisplace1->text().toInt();
}

void Settings::on_lineEdit_2_editingFinished()
{
    iterDisplace2 = ui->lineEdit_IterDisplace2->text().toInt();
}

/*
void Settings::on_lineEdit_3_editingFinished()
{
    dz = ui->lineEdit_3->text().toDouble();
}
*/
