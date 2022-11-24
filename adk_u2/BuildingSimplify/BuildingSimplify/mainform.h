#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QtGui>

QT_BEGIN_NAMESPACE
namespace Ui { class MainForm; }
QT_END_NAMESPACE

class MainForm : public QWidget
{
    Q_OBJECT

public:
    MainForm(QWidget *parent = nullptr);
    ~MainForm();

private slots:

    void on_clear_clicked();

    void on_simplify_clicked(std::vector <QPointF> &points);

    void on_load_data_clicked();

private:
    Ui::MainForm *ui;
};
#endif // MAINFORM_H
