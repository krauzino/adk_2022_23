#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainForm; }
QT_END_NAMESPACE

class MainForm : public QMainWindow
{
    Q_OBJECT

private:
    int iterDisplace1, iterDisplace2;

public:
    MainForm(QWidget *parent = nullptr);
    ~MainForm();

private slots:   
    void on_actionOpen_element_triggered();
    void on_actionOpen_barrier_triggered();
    void on_actionElement_Barrier_changed();
    void on_actionDisplace_triggered();
    void on_actionDisplace_2_elements_triggered();
    void on_actionClear_all_triggered();

private:
    Ui::MainForm *ui;
};
#endif // MAINFORM_H
