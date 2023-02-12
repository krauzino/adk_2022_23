#include "mainform.h"
#include "ui_mainform.h"
#include "algorithms.h"
#include "draw.h"
#include "csv.h"
#include <iostream>
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
MainForm::MainForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);


    // Initialization
    zmin = 0;
    zmax = 1000;
    dz = 10;

}

MainForm::~MainForm()
{
    delete ui;
}


void MainForm::on_actionOpen_triggered()
{
    //Open file and import data

    //Create Minmax box coors for our data
    double x_min =  10.e10;
    double x_max = -10.e10;
    double y_min =  10.e10;
    double y_max = -10.e10;

    //Choose data
    QString path(QFileDialog::getOpenFileName(this, tr("Open file with polygons"), "../", tr("CSV Files (*.csv)")));

    //Convert to string path
    std::string filename = path.toStdString();
if (filename.length() > 0)
    {
    //Read the chosen file
    std::vector<std::vector<std::string>> csv_content = CSV::read_csv(filename);

    std::vector<QPoint3D> points_3d = CSV::getPoints3D(csv_content, x_min, x_max, y_min, y_max);

    //Get canvas size
    int canvas_width = ui->Canvas->size().width();
    int canvas_height = ui->Canvas->size().height();

    //Get size ratio for transformation to canvas
    double dataset_width = x_max - x_min;
    double dataset_height = y_max - y_min;
    double x_ratio = canvas_width/dataset_width;
    double y_ratio = canvas_height/dataset_height;

    //Get proper scale for whole dataset visibility without deformation
    double scale;
    if (x_ratio < y_ratio)
        scale = x_ratio;
    else
        scale = y_ratio;
    ui->Canvas->setScale(scale);

    // Coordinates of top left corner of the canvas
    int x_left_top = ui->Canvas->geometry().x();
    int y_left_top = ui->Canvas->geometry().y();

    //Get left top corner (origin offset)
    int offset_x = ui->Canvas->x();
    int offset_y = ui->Canvas->y();

    //Set offsets
    ui->Canvas->setOffsets(offset_x, offset_y);

    // Translation parameter for transformation
    double x_trans = x_min - x_left_top;
    double y_trans = y_min - y_left_top;

    //Set translations
    ui->Canvas->setTrans(x_trans, y_trans);

    //Draw points
    ui->Canvas->drawCSVPoints(points_3d);    
}
}

void MainForm::on_actionCreate_DT_triggered()
{
    //Create Delaunay triangulation
    // Get points
    std::vector <QPoint3D> points = ui->Canvas->getPoints();

    // Create DT
    Algorithms a;
    std::vector <Edge> dt = a.createDT(points);

    // Update DT
    ui->Canvas->setDT(dt);

    repaint();
}


void MainForm::on_actionExit_triggered()
{
    //Exit application
    exit(0);
}


void MainForm::on_actionCreate_contour_lines_triggered()
{
    //Create contour lines  
    // Clear contour lines
    ui->Canvas->clearContours();

    // Get points
    std::vector <QPoint3D> points = ui->Canvas->getPoints();

    // Create DT
    Algorithms a;

    //Get Delaunay triangulation
    std::vector <Edge> dt = ui->Canvas->getDT();

    // DT wasn't created yet
    if(dt.size()==0)
    {
        dt = a.createDT(points);

        // Update DT
        ui->Canvas->setDT(dt);
    }

    // Generate contour lines
    std::vector<Edge> contours = a.createContourLines(dt, zmin, zmax, dz);

    // Update DT
    ui->Canvas->setContours(contours);

    repaint();
}


void MainForm::on_actionAnalyze_slope_triggered()
{
    //Analyze slope
    // Clear triangles
    ui->Canvas->clearTriangles();
    // Get points
    std::vector <QPoint3D> points = ui->Canvas->getPoints();

    // Create DT
    Algorithms a;

    //Get Delaunay triangulation
    std::vector <Edge> dt = ui->Canvas->getDT();

    // DT wasn't created yet
    if(dt.size()==0)
    {
        dt = a.createDT(points);

        // Update DT
        ui->Canvas->setDT(dt);
    }


    // Compute slope
    std::vector<Triangle> triangles = a.analyzeSlope(dt);
    ui->Canvas->switchSlope();


    // Update DT
    ui->Canvas->setTriangles(triangles);

    double min = Algorithms::getMinSlope(triangles);
    double max = Algorithms::getMaxSlope(triangles);
    ui->Canvas->setMinSlope(min);
    ui->Canvas->setMaxSlope(max);

    repaint();
}


void MainForm::on_actionAnalyze_aspect_triggered()
{
    //Analyze aspect
    // Clear triangles
    ui->Canvas->clearTriangles();
    // Get points
    std::vector <QPoint3D> points = ui->Canvas->getPoints();

    // Create DT
    Algorithms a;

    //Get Delaunay triangulation
    std::vector <Edge> dt = ui->Canvas->getDT();

    // DT wasn't created yet
    if(dt.size()==0)
    {
        dt = a.createDT(points);

        // Update DT
        ui->Canvas->setDT(dt);
    }

    // Compute slope
    std::vector<Triangle> triangles = a.analyzeAspect(dt);

    // Update DT
    ui->Canvas->setTriangles(triangles);

    double min = Algorithms::getMinSlope(triangles);
    double max = Algorithms::getMaxSlope(triangles);
    ui->Canvas->setMinSlope(min);
    ui->Canvas->setMaxSlope(max);

    repaint();
}


void MainForm::on_action_2_triggered()
{
    //OK button
    if (settings.exec() == QDialog::Accepted)
    {
        //Set properties
        zmin = settings.getZmin();
        zmax = settings.getZmax();
        dz = settings.getDz();
    }
}

void MainForm::on_actionClear_all_triggered()
{
    ui->Canvas->clearPoints();
    ui->Canvas->clearContours();
    ui->Canvas->clearTriangles();
    ui->Canvas->clearDT();
    repaint();
}


void MainForm::on_actionClear_slope_aspect_triggered()
{
    ui->Canvas->clearTriangles();
    ui->Canvas->clearDT();
    repaint();
}
