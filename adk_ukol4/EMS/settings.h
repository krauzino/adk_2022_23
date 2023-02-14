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

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

    int getIterDispl1() {return iterDisplace1;}
    int getIterDispl2() {return iterDisplace2;}

private slots:
    void on_lineEdit_editingFinished(); // co tento nazev??

    void on_lineEdit_2_editingFinished();

    //void on_lineEdit_3_editingFinished();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
