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

void MainForm::simplifyBuildings(std::vector <QPointF> &points)
{
    // Create enclosing rectangle
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
    ui->Canvas->setMAER(err);
    repaint();
}


void MainForm::on_simplify_clicked()
{
    // Get points and polygons
    std::vector<QPointF> points = ui->Canvas->getPoints();
    std::vector<QPolygonF> polygons = ui->Canvas->getPolygons();

    // Create enclosing rectangle
    Algorithms a;
    std::vector<QPointF> points_of_polygon;

    // Simplify buildings
    if (points.size() > 1) simplifyBuildings(points);

    // Process data
    if (polygons.size() > 0)
        for (QPolygonF polygon : polygons)
        {
            points_of_polygon.clear();
            for (QPointF point : polygon)
                points_of_polygon.push_back(point);

            if (points_of_polygon.size() > 0)
                simplifyBuildings(points_of_polygon);
        }

    // Clear created convex hulls and/or enclosing rectangles
    ui->Canvas->clearCH();
    ui->Canvas->clearMAER();
}


void MainForm::on_load_data_clicked()
{
    CSV csvObject;
    double xmin =  1e13;
    double xmax = -1e13;
    double ymin =  1e13;
    double ymax = -1e13;

    // Choose file
    QString file_path(QFileDialog::getOpenFileName(this, tr("Open CSV file with polygons"), "../", tr("CSV files (*.csv)")));

    // Convert to string path
    std::string filename = file_path.toStdString();

    // Read chosen file
    std::vector<QPolygonF> polygonVector = csvObject.readCSV(filename, xmin, xmax, ymin, ymax);

    // Get canvas size
    int canvas_width = ui->Canvas->size().width();
    int canvas_height = ui->Canvas->size().height();

    // Size ratio for transformation to canvas
    double data_width = xmax - xmin;
    double data_height = ymax - ymin;
    double xratio = data_width/canvas_width;
    double yratio = data_height/canvas_height;

    // Coordinates of the top left corner of the canvas
    int xtopL = ui->Canvas->geometry().x();
    int ytopL = ui->Canvas->geometry().y();

    // Translation
    double xtrans = xmin - xtopL;
    double ytrans = ymin - ytopL;

    // Draw polygons
    ui->Canvas->drawPolygons(polygonVector, xtrans, ytrans, xratio, yratio);
}


void MainForm::on_clear_clicked()
{
    // Clear all
    ui->Canvas->clearAll();
    repaint();
}
