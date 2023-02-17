#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT
private:
    int iterDisplace1, iterDisplace2;
    double dmin, alfa, gamma, beta, lambda;

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

    int getIterDispl1() {return iterDisplace1;}
    int getIterDispl2() {return iterDisplace2;}
    double getdmin() {return dmin;}
    double getalfa() {return alfa;}
    double getbeta() {return beta;}
    double getgamma() {return gamma;}
    double getlambda() {return lambda;}

private slots:
    /*
    void on_lineEdit_editingFinished(); //

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_3_editingFinished();

    void on_lineEdit_4_editingFinished(); //

    void on_lineEdit_5_editingFinished();

    void on_lineEdit_6_editingFinished();

    void on_lineEdit_7_editingFinished();
*/
    void on_lineEdit_dmin_editingFinished();

    void on_lineEdit_alfa_editingFinished();

    void on_lineEdit_beta_editingFinished();

    void on_lineEdit_gamma_editingFinished();

    void on_lineEdit_lambda_editingFinished();

    void on_lineEdit_IterDisplace1_editingFinished();

    void on_lineEdit_IterDisplace2_editingFinished();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
