#include "mainform.h"
#include "ui_mainform.h"
#include "algorithms.h"
#include "csv.h"
#include "draw.h"

#include <string>
#include <iostream>
#include <QFileDialog>
#include <vector>


MainForm::MainForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);
}

MainForm::~MainForm()
{
    delete ui;
}


void MainForm::on_simplify_clicked(std::vector <QPointF> &points)
{
    // Get building
    Algorithms a;
    QPolygonF err;

    if (ui->comboBox->currentText() == "Minimum Area Rectangle")
    {
        // Minimum area enclosing rectangle
        QPolygonF ch = a.createCH(points);
        err = a.minAreaEnclosingRectangle(points);
        ui->Canvas->setCH(ch);
    }

    else if (ui->comboBox->currentText() == "Wall Average")
    {
        // Wall average
        err = a.wallAverage(points);
    }

    else if (ui->comboBox->currentText() == "Longest Edge")
    {
        // Longest Edge
        err = a.longestEdge(points);
    }

    // Set result and repaint
    ui->Canvas->setMinimumAreaEnclosingRectangle(err);
    repaint();
}


void MainForm::on_load_data_clicked()
{
    CSV csvObject;
    double xmin =  1e10;
    double xmax = -1e10;
    double ymin =  1e10;
    double ymax = -1e10;

    // Choose file
    QString file_path(QFileDialog::getOpenFileName(this, tr("Open CSV with polygons"), "../", tr("CSV Files (*.csv)")));

    // Convert to string path
    std::string filename = file_path.toStdString();

    // Read the chosen file
    std::vector<QPolygonF> polygonVector = csvObject.read_CSV(filename, xmin, xmax, ymin, ymax);

    // Get canvas size
    int canvas_width = ui->Canvas->size().width();
    int canvas_height = ui->Canvas->size().height();

    // Size ratio for transformation to canvas
    double data_width = xmax - xmin;
    double data_height = ymax - ymin;
    double x_ratio = data_width/canvas_width;
    double y_ratio = data_height/canvas_height;

    // Coordinates of top left corner of the canvas
    int xtopL = ui->Canvas->geometry().x();
    int ytopL = ui->Canvas->geometry().y();

    // Translation parameter for transformation
    double x_trans = xmin - xtopL;
    double y_trans = ymin - ytopL;

    // Draw polygons
    ui->Canvas->drawPolygons(polygonVector, x_trans, y_trans, x_ratio, y_ratio);
}


void MainForm::on_clear_clicked()
{
    // Clear all
    ui->Canvas->clearAll();
    repaint();
}
