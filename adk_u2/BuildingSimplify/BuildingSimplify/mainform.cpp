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


void MainForm::on_simplify_clicked()
{
    // Get building
    QPolygonF building = ui->Canvas->getBuild();
    Algorithms a;
    Draw d;
    QPolygonF err;

    if (ui->comboBox->currentText() == "Minimum Area Rectangle")
    {

        // Minimum Area Enclosing Rectangle
        err = a.resizeMinAreaEnclosingRectangle(building);
    }

    else if (ui->comboBox->currentText() == "Wall Average")
    {
        // Wall average
        err = a.wallAverage(building);
    }

    else if (ui->comboBox->currentText() == "Longest Edge")
    {
        // Longest Edge
        err = a.longestEdge(building);
    }

    // Set result and repaint
    ui->Canvas->setMinimumAreaEnclosingRectangle(err);
    repaint();

}


void MainForm::on_load_data_clicked()
{
    CSV csvObject;
    //MMB coordinates
    double xmin =  1000000000;
    double xmax = -1000000000;
    double ymin =  1000000000;
    double ymax = -1000000000;

    // Choose file
    QString file_path(QFileDialog::getOpenFileName(this, tr("Open CSV with polygons"), "../", tr("CSV Files (*.csv)")));

    // Convert to string path
    std::string filename = file_path.toStdString();

    // Read the chosen file
    std::vector<QPolygonF> polygonVector = csvObject.read_CSV(filename, xmin, xmax, ymin, ymax);

    // Get size of the Canvas
    int canvas_width = ui->Canvas->size().width();
    int canvas_height = ui->Canvas->size().height();

    // Size scale for transformation to canvas
    double data_width = xmax - xmin;
    double data_height = ymax - ymin;
    double x_ratio = data_width/canvas_width;
    double y_ratio = data_height/canvas_height;

    // Find coords of top left corner in Canvas
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
