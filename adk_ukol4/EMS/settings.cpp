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
    dmin = 100;
    alfa = 0.3;
    beta = 1000;
    gamma = 1000;
    lambda = 20;
  //  dz = 10;

    // Set default values to line edits
    ui->lineEdit_IterDisplace1->setText(QString::number(iterDisplace1));
    ui->lineEdit_IterDisplace2->setText(QString::number(iterDisplace2));
    ui->lineEdit_dmin->setText(QString::number(dmin));
    ui->lineEdit_alfa->setText(QString::number(alfa));
    ui->lineEdit_beta->setText(QString::number(beta));
    ui->lineEdit_gamma->setText(QString::number(gamma));
    ui->lineEdit_lambda->setText(QString::number(lambda));
    //  ui->lineEdit_3->setText(QString::number(dz));

}

Settings::~Settings()
{
    delete ui;
}
/*
void Settings::on_lineEdit_editingFinished()
{
    iterDisplace1 = ui->lineEdit_IterDisplace1->text().toInt();
}

void Settings::on_lineEdit_2_editingFinished()
{
    iterDisplace2 = ui->lineEdit_IterDisplace2->text().toInt();
}
void Settings::on_lineEdit_3_editingFinished()
{
    dmin = ui->lineEdit_dmin->text().toDouble();
}

void Settings::on_lineEdit_4_editingFinished()
{
    alfa = ui->lineEdit_alfa->text().toDouble();
}
void Settings::on_lineEdit_5_editingFinished()
{
    beta = ui->lineEdit_beta->text().toDouble();
}
void Settings::on_lineEdit_6_editingFinished()
{
    gamma = ui->lineEdit_gamma->text().toDouble();
}

void Settings::on_lineEdit_7_editingFinished()
{
    lambda = ui->lineEdit_lambda->text().toDouble();
}


void Settings::on_lineEdit_3_editingFinished()
{
    dz = ui->lineEdit_3->text().toDouble();
}
*/


void Settings::on_lineEdit_dmin_editingFinished()
{
    dmin = ui->lineEdit_dmin->text().toDouble();
}

void Settings::on_lineEdit_alfa_editingFinished()
{
    alfa = ui->lineEdit_alfa->text().toDouble();
}

void Settings::on_lineEdit_beta_editingFinished()
{
    beta = ui->lineEdit_beta->text().toDouble();
}

void Settings::on_lineEdit_gamma_editingFinished()
{
    gamma = ui->lineEdit_gamma->text().toDouble();
}

void Settings::on_lineEdit_lambda_editingFinished()
{
    lambda = ui->lineEdit_lambda->text().toDouble();
}

void Settings::on_lineEdit_IterDisplace1_editingFinished()
{
    iterDisplace1 = ui->lineEdit_IterDisplace1->text().toInt();
}

void Settings::on_lineEdit_IterDisplace2_editingFinished()
{
    iterDisplace2 = ui->lineEdit_IterDisplace2->text().toInt();
}
